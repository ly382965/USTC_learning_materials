extern void oneTickUpdateWallClock(void);       //TODO: to be generalized
extern void schedulerTimerHandler(void);        // 新增：调度器时钟处理

void (*tick_hook)(void) = 0;

int tick_number = 0;
void tick(void){
     tick_number++;	

     oneTickUpdateWallClock();
     
     // 调用调度器的时钟处理函数
     schedulerTimerHandler();

     if(tick_hook) tick_hook();  //user defined   
}
