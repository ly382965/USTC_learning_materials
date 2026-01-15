extern void oneTickUpdateWallClock(void); 
//#ifndef __TICK_HOOK__
//#define __TICK_HOOK__
void (*tick_hook)(void) = 0; //{};
//#endif

int tick_number = 0;
void tick(void){
	int temp_col, temp_row;	
	tick_number++;	
	//myPrintk(0x4,"tick::%d\n",tick_number);

	oneTickUpdateWallClock();

	/* call hooks 
	scheduler_tick();  // RR
	tick_hook_arr();  // arriving	

	if(watchdogTimer_func) watchdogTimer_func(); 
    */
	if(tick_hook) tick_hook();  //user defined   
}
