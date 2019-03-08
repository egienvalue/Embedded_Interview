[Goback to Readme](./readme.md)

- [Free RTOS](#free-rtos)
  - [Task States](#task-states)
  - [Task Sychronization](#task-sychronization)
  - [Queue](#queue)
    - [Typical Design](#typical-design)
  - [Event Groups](#event-groups)

## Free RTOS

### Task States
Fours task states: running, blocked, ready, suspended
![](./IMG/FreeRTOS_TaskState.png)

The suspended state will enter only through calling the TaskSuspend().


### Task Sychronization

1. Mutex



2. Counting Semaphore
```c++
// Initialize
SemaphoreHandle_t xSemaphoreCreateCounting( UBaseType_t uxMaxCount, UBaseType_t uxInitialCount );

//
xCountingSemaphore = xSemaphoreCreateCounting( 10, 0 );

static uint32_t ulExampleInterruptHandler( void )
{
BaseType_t xHigherPriorityTaskWoken;
    /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as it
    will get set to pdTRUE inside the interrupt safe API function if a context switch
    is required. */
    xHigherPriorityTaskWoken = pdFALSE;
    /* 'Give' the semaphore multiple times.  The first will unblock the deferred
    interrupt handling task, the following 'gives' are to demonstrate that the
    semaphore latches the events to allow the task to which interrupts are deferred
    to process them in turn, without events getting lost.  This simulates multiple
    interrupts being received by the processor, even though in this case the events
    are simulated within a single interrupt occurrence. */
    xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
    xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
    xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
    /* Pass the xHigherPriorityTaskWoken value into portYIELD_FROM_ISR().  If
    xHigherPriorityTaskWoken was set to pdTRUE inside xSemaphoreGiveFromISR() then
    calling portYIELD_FROM_ISR() will request a context switch.  If
    xHigherPriorityTaskWoken is still pdFALSE then calling portYIELD_FROM_ISR() will
    have no effect. Unlike most FreeRTOS ports, the Windows port requires the ISR to
    return a value - the return statement is inside the Windows version of
    portYIELD_FROM_ISR(). */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

// Task to get the semaphore
static void vHandlerTask( void *pvParameters )
{
    /* As per most tasks, this task is implemented within an infinite loop. */
    for( ;; ) {
        /* Use the semaphore to wait for the event.  The semaphore was created
        before the scheduler was started, so before this task ran for the first
        time.  The task blocks indefinitely, meaning this function call will only
        return once the semaphore has been successfully obtained - so there is
        no need to check the value returned by xSemaphoreTake(). */
        xSemaphoreTake( xBinarySemaphore, portMAX_DELAY);
        /* To get here the event must have occurred.  Process the event (in this
        Case, just print out a message). */
        vPrintString( "Handler task - Processing event.\r\n" );
    } 
}
```

### Queue
Queues provide a task-to-task, task-to-interrupt, and interrupt-to-task communication mechanism. Queues are normally used as First In First Out (FIFO) buffers, where data is written to the end (tail) of the queue and removed from the front (head) of the queue. 

![](./IMG/FreeRTOS_Queue.png)

#### Typical Design

It is common in FreeRTOS designs for a task to receive data from more than one source. The receiving task needs to know where the data came from to determine how the data should be processed. An easy design solution is to use a single queue to transfer structures with both the value of the data and the source of the data contained in the structure’s fields. This scheme is demonstrated in Figure 34

![](./IMG/FreeRTOS_Queue_Usage.png)


### Event Groups
Features:
- Event groups allow a task to wait in the Blocked state for a combination of one of more events to occur.
- Event groups unblock all the tasks that were waiting for the same event, or combination of events, when the event occurs.
- These unique properties of event groups make them useful for synchronizing multiple tasks
- Event groups also provide the opportunity to reduce the RAM used by an application, as often it is possible to replace many binary semaphores with a single event group.

Each event will be represents by one bit in the Event group, if it has occured, the bit will be 1, otherwise it will be zero. The specific meaning of each bit in the event groups is specified by the user.
![](./IMG/FreeRTOS_EventFlag.png)

```c++
static void vEventBitReadingTask( void *pvParameters )
{
EventBits_t xEventGroupValue;
const EventBits_t xBitsToWaitFor = ( mainFIRST_TASK_BIT  | mainSECOND_TASK_BIT |
mainISR_BIT );
for( ;; ) {
/* Block to wait for event bits to become set within the event group. */
xEventGroupValue = xEventGroupWaitBits( /* The event group to read. */
                                        xEventGroup,
                                        /* Bits to test. */
                                        xBitsToWaitFor,
                                        /* Clear bits on exit if the
                                        unblock condition is met. */
                                        pdTRUE,
                                        /* Don't wait for all bits.  This
                                        parameter is set to pdTRUE for the
                                        second execution. */
                                        pdFALSE,
                                        /* Don't time out. */
                                        portMAX_DELAY );
/* Print a message for each bit that was set. */
if( ( xEventGroupValue & mainFIRST_TASK_BIT ) != 0 )
{
    vPrintString( "Bit reading task -\t Event bit 0 was set\r\n" );
}
if( ( xEventGroupValue & mainSECOND_TASK_BIT ) != 0 )
{
    vPrintString( "Bit reading task -\t Event bit 1 was set\r\n" );
}
if( ( xEventGroupValue & mainISR_BIT ) != 0 )
{
    vPrintString( "Bit reading task -\t Event bit 2 was set\r\n" );
}
} }



static void vEventBitSettingTask( void *pvParameters )
{
    const TickType_t xDelay200ms = pdMS_TO_TICKS(200UL), xDontBlock = 0;
for( ;; ) {

    /* Delay for a short while before starting the next loop. */
    vTaskDelay( xDelay200ms );
    /* Print out a message to say event bit 0 is about to be set by the task,
    then set event bit 0. */
    vPrintString( "Bit setting task -\t about to set bit 0.\r\n" );
    xEventGroupSetBits( xEventGroup, mainFIRST_TASK_BIT );
    /* Delay for a short while before setting the other bit. */
    vTaskDelay( xDelay200ms );
    /* Print out a message to say event bit 1 is about to be set by the task,
    then set event bit 1. */
    vPrintString( "Bit setting task -\t about to set bit 1.\r\n" );
    xEventGroupSetBits( xEventGroup, mainSECOND_TASK_BIT );
 
} 
}

```

Even synchronization allows multiple tasks synchronize one a specific time. For example, the TCP/IP tx task and TCP/IP rx task are sending and receiving data at the sametime. The tx task will close the socket only when the rx task finish the transmission. They need meet at specific point which both of them finish their tasks.

```c++
void SocketTxTask( void *pvParameters ) {
xSocket_t xSocket;
uint32_t ulTxCount = 0UL;
for( ;; ) {
/* Create a new socket. This task will send to this socket, and another task will receive from this socket. */
xSocket = FreeRTOS_socket( ... );
      /* Connect the socket. */
FreeRTOS_connect( xSocket, ... );
/* Use a queue to send the socket to the task that receives data. */
xQueueSend( xSocketPassingQueue, &xSocket, portMAX_DELAY);
/* Send 1000 messages to the socket before closing the socket. */
    for( ulTxCount = 0; ulTxCount < 1000; ulTxCount++ ) {
        if( FreeRTOS_send( xSocket, ... ) < 0 )
        {
            /* Unexpected error */
            break; 
        }
    }
    /* exit the loop, after which the socket will be closed.
    Tx task wants to close the socket. */
    /* Let the Rx task know the socket will close */
    TxTaskWantsToCloseSocket();
    /* This is the Tx task’s synchronization point. The Tx task waits here for the Rx task to reach its synchronization point. The Rx task will only reach its synchronization point when it is no longer using the socket, and the socket can be closed safely. */
    xEventGroupSync( ... );
    /* Neither task is using the socket. Shut down the connection, then close the socket. */
    FreeRTOS_shutdown( xSocket, ... ); WaitForSocketToDisconnect(); 
    FreeRTOS_closesocket( xSocket );
} }
/*-----------------------------------------------------------*/
void SocketRxTask( void *pvParameters ) {
xSocket_t xSocket;
for( ;; ) {
    /* Wait to receive a socket that was created and connected by the Tx task. */
    xQueueReceive( xSocketPassingQueue, &xSocket, portMAX_DELAY );
    /* Keep receiving from the socket until the Tx task wants to close the socket. */
    while( TxTaskWantsToCloseSocket() == pdFALSE ) {
          /* Receive then process data. */
          FreeRTOS_recv( xSocket, ... );
          ProcessReceivedData();
      }
    /* This is the Rx task’s synchronization point - it only reaches here when it is no longer using the socket, and it is therefore safe for the Tx task to close the socket. */ 
    xEventGroupSync( ... );
} }

```