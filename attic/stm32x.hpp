

/**
  * @brief  Sets System clock frequency to 72MHz and configure HCLK, PCLK2 
  *         and PCLK1 prescalers. 
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
   
  //  PLL configuration: PLLCLK = HSI/2 * 16 = 64 MHz 
  RCC->CFGR &= (uint32_t)((uint32_t)~( RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL ) );
  RCC->CFGR |= (uint32_t)( RCC_CFGR_PLLSRC_HSI_Div2 | RCC_CFGR_PLLMULL16 );
    
  // Wait till HSE is ready
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;  
  } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

 
   //  PLL configuration: PLLCLK = HSE * 9 = 72 MHz 
   RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                        RCC_CFGR_PLLMULL));
   RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9);
   
   // Enable Prefetch Buffer 
   FLASH->ACR |= FLASH_ACR_PRFTBE;

   // Flash 2 wait state 
   FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
   FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;    

   // HCLK = SYSCLK 
   RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
      
   // PCLK2 = HCLK 
   RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1;
    
   // PCLK1 = HCLK 
   RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2;

   // Enable PLL 
   RCC->CR |= RCC_CR_PLLON;

   // Wait till PLL is ready 
   while((RCC->CR & RCC_CR_PLLRDY) == 0){}
    
   // Select PLL as system clock source
   RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
   RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;    

   // Wait till PLL is used as system clock source
   while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08){}
}
