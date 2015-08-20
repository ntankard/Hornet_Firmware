//Communication Pins
const int rx = 0;
const int tx = 1;

//Connection request
char comRequest;

void setup() {
  // put your setup code here, to run once:
  // begin Serial commuication at 9600 baud rate
  Serial.begin(9600); 
  
  //Set pins for serial communication
  //pinMode(tx, OUTPUT);
  //pinMode(rx, INPUT);
}

void loop() {
  Serial.write('a');
  delay(1000);
  readCommand();
  if (comRequest == 'b'){
    while(true){
      //Set the ID byte as a LIDAR packet
      byte IDbyte = 'l';
      //Some fake data
      float lidarData[4] = {37, 131, 20, 15};
      //Add the ID to the packet
      byte packet[17] = {IDbyte};
      //Add the 4 floats to the packet
      for (int i=0; i<4; i++){
        byte floatByte[4];
        float2Bytes(lidarData[i],&floatByte[0]);
        for (int x=0; x<4; x++){
          packet[(i*4)+1+x] = floatByte[x]; 
        }
      }
      //Send packet
      Serial.write(packet, 17);
    }
  }
}

void float2Bytes(float val,byte* bytes_array){
  // Create union of shared memory space
  union {
    float float_variable;
    byte temp_array[4];
  } u;
  // Overite bytes of union with float variable
  u.float_variable = val;
  // Assign bytes to input array
  memcpy(bytes_array, u.temp_array, 4);
}

void readCommand(){
  if (Serial.available()) {
    comRequest = Serial.read();
    delay(50);
  }
}
