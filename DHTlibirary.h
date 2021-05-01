
#include<windows.h>
#include <Arduino.h>
#include <wire.h>


class DHT
{
private:
    int pin;
	unsigned char RH_int , RH_dec , T_int , T_dec , sum , pulse[80], lowCycle, highCycle;
public: 
    //constructor to initialize the data
    DHT(int Pin)
	{
        //Serial.begin(9600);
        pin = Pin;
        RH_int = 0, RH_dec = 0, T_int = 0, T_dec = 0, sum = 0, pulse[80];
	}

    //function to calculate the time until the signal change
    int expectPulse(bool lvl)
    {
        int count = 0;
        while (digitalRead(pin) == lvl) count++;
        return count;
    }

    //doing all the calculation to get the temperature and RH
	bool compute()
	{
		pinMode(pin, OUTPUT);
		digitalWrite(pin, HIGH);
		Sleep(1000);
		digitalWrite(pin, LOW);
		Sleep(18);
		digitalWrite(pin, HIGH);
		Sleep(0.04);
		pinMode(pin, INPUT);
		if (digitalRead(pin) == LOW)
		{
			while (digitalRead(pin) == LOW)
			{
			}
			while (digitalRead(pin) == HIGH)
			{
			}
		}
		else
		{   
            
            {
                return 0;
            }
            for (int i = 0; i < 80; i++)
                pulse[i] = expectPulse(i % 2);
            for (int i = 0; i < 40; i++)
            {
                lowCycle = pulse[i * 2];
                highCycle = pulse[(i * 2) + 1];
                if (i < 8)
                {
                    RH_int <<= 1;
                    if (highCycle > lowCycle) RH_int |= 1;
                }
                if (i < 16)
                {
                    RH_dec <<= 1;
                    if (highCycle > lowCycle) RH_dec |= 1;
                }
                if (i < 24)
                {
                    T_int <<= 1;
                    if (highCycle > lowCycle) T_int |= 1;
                }
                if (i < 32)
                {
                    T_dec <<= 1;
                    if (highCycle > lowCycle) T_dec |= 1;
                }
                if (i < 40)
                {
                    sum <<= 1;
                    if (highCycle > lowCycle) sum |= 1;
                }
            }
            if (sum != RH_int + RH_dec + T_int + T_dec)
            {
                return 0;
            }
            else
            {
                return 1;
            }
		}
	}

    //function to get the temperature
    float getT()
    {
        if (compute)
            return (float)T_int + (float)T_dec / 100;
        else
            return 0;
    }

    //function to get the Humidity
    float getRH()
    {
        if (compute)
            return (float)RH_int + (float)RH_dec / 100;
        else return 0;
    }
};
	


