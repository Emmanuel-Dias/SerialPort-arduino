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

#define clk_time 2

class SerialPort{
    public:
        SerialPort(int data, int port, int clear, int clr){
            _data= data;    // module
            _port= port;    // port
            _clear= clear;  // clear module
            _clr= clr;      // clear controller

            pinMode(_data, OUTPUT);
            pinMode(_port, OUTPUT);
            pinMode(_clear, OUTPUT);
            pinMode(_clr, OUTPUT);
        }

        string clear_module(int module){
            request_module(module);
            request_port(5, true);
        }

        string call(int module, string port){
            if(module >= 0 && module <= 15){
                request_module(module);

                if(port == "S0"){
                    request_port(1);
                    return "[SUCCESS] !> port S0 successfully modified";
                }
                else if(port == "S1"){
                    request_port(2);
                    return "[SUCCESS] !> port S1 successfully modified";
                }
                else if(port == "S2"){
                    request_port(3);
                    return "[SUCCESS] !> port S2 successfully modified";
                }
                else{
                    return "[ ERROR ] !> port index out of range";
                }
            }
            else{
                return "[ ERROR ] !> module index out of range";
            }
        }

    private:
        void request_module(int clk){
            digitalWrite(_clr, HIGH);
            delay(clk_time);
            digitalWrite(_clr, LOW);

            for(int i=0; i<clk; i++){
                digitalWrite(_data, HIGH);
                delay(clk_time);
                digitalWrite(_data, LOW);
            }
        }

        void request_port(int clk, bool clear= false){
            if(clk <= 4 && clear == false){
                digitalWrite(_clear, HIGH);
                delay(clk_time);
                digitalWrite(_clear, LOW);

                for(int i=0; i<clk; i++){
                    digitalWrite(_port, HIGH);
                    delay(clk_time);
                    digitalWrite(_port, LOW);
                }
            else if(clk == 5 && clear == true){
                digitalWrite(_clear, HIGH);
                delay(clk_time);
                digitalWrite(_clear, LOW);

                for(int i=0; i<clk; i++){
                    digitalWrite(_port, HIGH);
                    delay(clk_time);
                    digitalWrite(_port, LOW);
                }
            }
        }
}
