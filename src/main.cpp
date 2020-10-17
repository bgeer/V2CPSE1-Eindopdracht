#include "hwlib.hpp"
#include "ownSpiBus.hpp"

namespace target = hwlib::target;

int main( void ){
   
   // wait for the terminal emulator to start up
   hwlib::wait_ms( 2'000 );
   hwlib::cout << "ST7789 demo\n" << hwlib::flush;   
   
   auto _sclk = hwlib::target::pin_out{ hwlib::target::pins::d3 };
   auto sclk = hwlib::invert( _sclk );
   auto mosi = hwlib::target::pin_out{ hwlib::target::pins::d4 };
   
   auto spi  = hwlib::ownSpiBus{ 
      sclk, mosi, hwlib::pin_in_dummy };
      
   auto dc    = hwlib::target::pin_out{ hwlib::target::pins::d6 };
   auto & cs  = hwlib::pin_out_dummy;
   auto blk   = hwlib::target::pin_out{ hwlib::target::pins::d7 };
   auto rst   = hwlib::target::pin_out{ hwlib::target::pins::d5 };
   
   blk.write( 1 );blk.flush();

   auto display     = hwlib::st7789_spi_dc_cs_rst( spi, dc, cs, rst );   
   
   for(;;){
      //used 4 timings, 2 for each because maybe hwlib::cout takes also time.
      auto t1 = hwlib::now_us();
      display.clear( hwlib::red );
      auto t2 = hwlib::now_us();
      auto timeItTook = t2-t1;
      hwlib::cout<<timeItTook << " Microseconds it took to clear" << hwlib::endl;
      auto t3 = hwlib::now_us();
      display.flush();
      auto t4 = hwlib::now_us();
      timeItTook = t4-t3;
      hwlib::cout<<timeItTook << " Microseconds it took to flush" << hwlib::endl;

      display.clear( hwlib::green );
      display.flush();

      display.clear( hwlib::blue );
      display.flush();
   }
   
}
