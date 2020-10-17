/// bit-banged SPI bus implementation
///
/// This class implements a bit-banged master interface to a SPI bus.
#include "hwlib.hpp"

namespace hwlib{

class ownSpiBus : public spi_bus {
private:

   pin_direct_from_out_t sclk;
   pin_direct_from_out_t mosi;
   pin_direct_from_in_t  miso;
   
   // very crude;
   // delay should be a constructor parameter
   void HWLIB_INLINE wait_half_period(){
      wait_us( 1 );      
   }
   
   void write_and_read( 
      const size_t n, 
      const uint8_t data_out[],
      uint8_t data_in[]          //deze had ook weggekund maar dat vind hwlib spibus.hpp niet leuk.
   ) override {
      // for( uint_fast8_t i = 0; i < n; ++i ){
          
         uint_fast8_t d = *data_out++;

         // uint_fast8_t d = 
         //    ( data_out == nullptr )
         //    ? 0 
         //    : *data_out++;
             
         for( uint_fast8_t j = 0; j < 8; ++j ){
         // wait_half_period();
            mosi.write( ( d & 0x80 ) != 0 );
            // wait_half_period();
            sclk.write( 1 );
            // wait_half_period();
            d = d << 1;
            // if( miso.read() ){
            //    d |= 0x01;
            // }
            sclk.write( 0 );              
         }
          
         // if( data_in != nullptr ){
         //    *data_in++ = d;
         // }
      // }      
      // wait_half_period();
   }      
   
public:

   /// construct a bit-banged SPI bus from the sclk, miso and mosi pins
   ///
   /// This constructor creates a simple bit-banged SPI bus master
   /// from the sclk, miso and mosi pins. 
   ///
   /// The chip select pins for the individual chips supplied to the 
   /// write_and_read() functions.
   ///
   /// When the SPI bus is used for either only writing or only reading,
   /// the unused pin argument can be specified as pin_out_dummy or
   /// pin_in_dummy.
   ownSpiBus( 
      pin_out & _sclk, 
      pin_out & _mosi, 
      pin_in  & _miso 
   ):
      //sclk( direct( _sclk ) ), 
      //mosi( direct( _mosi ) ), 
      //miso( direct( _miso ) )
      
      sclk( _sclk ), 
      mosi( _mosi ), 
      miso( _miso ){
      sclk.write( 0 );
   }
}; // class ownSpiBus 
}