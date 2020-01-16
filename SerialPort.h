/* ------------------------------------------------------------------------------
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  ------------------------------------------------------------------------------ */

#ifndef SerialPort
#define SerialPort

#include <Arduino.h>

class SerialPort{
    public:
        SerialPort(int _port_A, int _port_B, int _port_CLR, int _port_clear, int _port_CLK){
            port_a= _port_A;            // port of data 01
            port_b= _port_B;            // port of data 02
            port_clr= _port_CLR;        // port of count clear
            port_clear= _port_clear;    // port of clear output modules
            port_clk= _port_CLK;        // port of clock controller

            int clock_time= 2;          // ms

        }

        void _clear(int module= -1){
            // clear the output module
            // -1 equal all modules
            if(module == -1){
                digitalWrite(port_clear, HIGH);

                for(int x=0; x < 15; x++){
                    digitalWrite(port_clr, HIGH);
                    delay(clock_time);
                    digitalWrite(port_clr, LOW);
                }

                digitalWrite(port_clear, LOW);
            }
            else{
                count_module(module);
                digitalWrite(port_clear, HIGH);
                delay(clock_time);
                digitalWrite(port_clear, LOW);
            }
        }

        string _call(int module, string port){
            // alternate the state of port from module
            if(module >= 0 && module <= 15){
                digitalWrite(port_a, LOW);
                digitalWrite(port_b, LOW);

                count_module(module);

                if(port == "S0"){
                    digitalWrite(port_a, LOW);
                    digitalWrite(port_b, HIGH);
                    return "[SUCCESS] port > S0 < modify your state";
                }
                else if(port == "S1"){
                    digitalWrite(port_a, HIGH);
                    digitalWrite(port_b, LOW);
                    return "[SUCCESS] port > S1 < modify your state";
                }
                else if(port == "S2"){
                    digitalWrite(port_a, HIGH);
                    digitalWrite(port_b, HIGH);
                    return "[SUCCESS] port > S2 < modify your state";
                }
                else{ return "[ ERROR ] ?> port index out of range"; }
                
            }
            else{ return "[ ERROR ] ?> module index out of range"; }
        }

    
    private:
        void count_module(int module){
            digitalWrite(port_clr, HIGH);
            delay(clock_time);
            digitalWrite(port_clr, LOW);

            for(int x=0; x < module; x++){
                digitalWrite(port_clr, HIGH);
                delay(clock_time);
                digitalWrite(port_clr, LOW);
            }
        }
}
