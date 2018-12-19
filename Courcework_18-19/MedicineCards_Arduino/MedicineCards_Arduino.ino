#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

String codingKey = "whd22fke";
String cardID = "_";
int cardDisconnectTimeout = 0;
bool isPCConnected = false;

void notifyCardConnected()
{
  if(isPCConnected)
    Serial.print((String)EncodingData(cardID, true)+"\n");
}

bool checkTimeout()
{
  if(cardDisconnectTimeout >= 4)
  {
    cardDisconnectTimeout = 0;
    return false;
  }else
  {
    cardDisconnectTimeout++;
    return true;
  }
}

bool checkCard()
{
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return checkTimeout();
  }  
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return checkTimeout();
  }  

  cardDisconnectTimeout = 0;
  String nowCardID = "";
  for(byte i = 0; i < mfrc522.uid.size; i++)
    nowCardID.concat(String(mfrc522.uid.uidByte[i], HEX));

  if(!nowCardID.equals(cardID))
  {
    cardID = nowCardID;
    notifyCardConnected();        
  }
  return true;    
}
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop()
{
  if(!checkCard())
    cardID = "_";
  
  if(Serial.available() > 0)
  {    
    char c = Serial.read();
    if(c == '?')
    {
      Serial.print("CardReader\n");
    }else if(c == '=')      
      notifyCardConnected();
    else if(c == '+')
      isPCConnected = true;
    else if(c == '-')
      isPCConnected = false;
  }
}

String EncodingData(String data, bool isCode)
{
    String encodedStr = "";
    for(int i = 0; i < data.length(); i++)
        if(isCode)
            encodedStr += (char)((data[i]+codingKey[i%codingKey.length()])%256);
        else
            encodedStr += (char)((data[i]-codingKey[i%codingKey.length()]+256)%256);
   
    return encodedStr;
}
