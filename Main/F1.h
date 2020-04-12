void F1A_PlayMenu();
void F1B_Go();

void GOOO();
void LetsGOOO(int responseLetsGo);

int doAction(int statusDoAction);
//void doActionBerhenti();
void doActionBelokKiri();

// ========== Action ==========
// 0 > (kosong)
// 1 > Berhenti
// 2 > Maju
// 3 > Belok Kiri
// 4 > Belok Kanan
// 5 > Balik Kiri
// 6 > Balik Kanan
// 7 > Lift On
// 8 > Lift Off
// 9 > Buzzer On
// 10 > Buzzer Off
// 11 > DO 01,LOW
// 12 > DO 01,HIGH
// 13 > DO 02,LOW
// 14 > DO 02,HIGH
// 15 > DO 03,LOW
// 16 > DO 03,HIGH
// 17 > DO 04,LOW
// 18 > DO 04,HIGH
// 19 > DO 05,LOW
// 20 > DO 05,HIGH

void F1A_PlayMenu(){
  pageF1A.show();
  Serial.println("F1A_PlayMenu");
  Gmode = 1;
  nF1ANum.setValue(Gmode);

//  for(int i = 1; i <= jumlahData; i++){
//    Serial.print(i);                Serial.print("_");
//    Serial.print(modeKe[i]);        Serial.print("_");
//    Serial.print(typeKe[i]);        Serial.print("_");
//    Serial.print(triggerKe[i]);     Serial.print("_");
//    Serial.print(actionKe[i]);      Serial.print("\n");
//  }
  
  
  while(true){
    nexLoop(nex_listen_list_F1A_PlayMenu);
    switch(Tombol){
      case tBACK:
        Tombol = tIDLE;
        Serial.println("bF1ABack");
        Menu = F0;
        return false;
        break;
      case tNEXT:
        Tombol = tIDLE;
        Serial.println("bF1ANext");
        F1B_Go();
        pageF1A.show();
        Serial.println("F1A_PlayMenu");
        nF1ANum.setValue(Gmode);
        break;
      case tMINUS:
        Tombol = tIDLE;
        Serial.println("bF1AMinus");
        nF1ANum.getValue(&Gmode);
        Gmode -= 1;
        if(Gmode <= 1)            Gmode = 1;
        if(Gmode >= jumlahData)   Gmode = jumlahData;
        nF1ANum.setValue(Gmode);
        break;
      case tPLUS:
        Tombol = tIDLE;
        Serial.println("bF1APlus");
        nF1ANum.getValue(&Gmode);
        Gmode += 1;
        if(Gmode <= 1)            Gmode = 1;
        if(Gmode >= jumlahData)   Gmode = jumlahData;
        nF1ANum.setValue(Gmode);
        break;
      default:
        break;
    }
  }
}


String nextTarget;
String prevTarget = "";
int urutanKe;

void F1B_Go(){
  pageF1B.show();
  Serial.println("F1B_Go");
// ================== disini untuk menentukan siapa si Next Target ============================
  int totalKe[1+jumlahData];
  for(int i = 1; i <= jumlahData; i++){ // reset totalKe[]
    totalKe[i] = 0;
    Serial.print(totalKe[i]);
  }
  
  Serial.println("\n");
  for(int j = 1; j <= jumlahData; j++){
    for(int i = 1; i <= jumlahData; i++){
      if(modeKe[i] == j){
        totalKe[j] += 1;
      }
    }
  }
  urutanKe = 0;
  for(int i = 1; i < Gmode; i++){
    Serial.println(totalKe[i]);
    urutanKe += totalKe[i];
  }
  urutanKe = urutanKe + 1;
  
  if(typeKe[urutanKe] == 1){
    nextTarget = idRFID[urutanKe]; 
  }
  else if(typeKe[urutanKe] == 2){
    nextTarget = stringDI(triggerKe[urutanKe]);
  }
  else{
    nextTarget = "TIDAK ADA";
  }
  Serial.print("Gmode       : ");  Serial.println(Gmode);
  Serial.print("urutanKe    : ");  Serial.println(urutanKe);
  Serial.print("TIPEnya     : ");  Serial.println(typeKe[urutanKe]);
  Serial.print("TRIGGER DI  : ");  Serial.println(triggerKe[urutanKe]);
  Serial.print("nextTarget  : ");  Serial.println(nextTarget);
  
  nF1BMode.setValue(Gmode);
  Serial2.print("gF1BStatusMode.txt=");
  Serial2.print("\"");
  Serial2.print("Stanby <->");
  Serial2.print("\"");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  
  Serial2.print("tF1BNextID.txt=");
  Serial2.print("\"");
  Serial2.print(nextTarget);
  Serial2.print("\"");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff); 
  
  while(true){
    nexLoop(nex_listen_list_F1B_Go);
    switch(Tombol){
      case tCANCEL:
        Tombol = tIDLE;
        Serial.println("bF1BCancel");
        return false;
        break;
      case tSTOP:
        Tombol = tIDLE;
        Serial.println("bF1BStop");

        Serial2.print("gF1BStatusMode.txt=");
        Serial2.print("\"");
        Serial2.print("Stop  X");
        Serial2.print("\"");
        Serial2.write(0xff);
        Serial2.write(0xff);
        Serial2.write(0xff);

        Serial2.print("bF1BGo.bco=");
        Serial2.print(50712);
        Serial2.write(0xff);
        Serial2.write(0xff);
        Serial2.write(0xff);
        
        break;
      case tGO:
        Tombol = tIDLE;
        Serial.println("bF1BGo");
        
        for(int i = 3; i >= 1; i--){    // count down for go
          Serial2.print("gF1BStatusMode.txt=");
          Serial2.print("\"");
          Serial2.print(i);
          Serial2.print("\"");
          Serial2.write(0xff);
          Serial2.write(0xff);
          Serial2.write(0xff);
          delay(100);
        }
        
        Serial2.print("gF1BStatusMode.txt=");
        Serial2.print("\"");
        Serial2.print("Jalan  -->>");
        Serial2.print("\"");
        Serial2.write(0xff);
        Serial2.write(0xff);
        Serial2.write(0xff);

        Serial2.print("bF1BGo.bco=");
        Serial2.print(1500);
        Serial2.write(0xff);
        Serial2.write(0xff);
        Serial2.write(0xff);

        GOOO();
        
      default:
        break;
    }
  }
}

int response = 0;

void GOOO(){
  response = 0;
  Serial.println("GO GO Gooo");

  Serial2.print("tF1BNextID.txt=");
  Serial2.print("\"");
  Serial2.print(nextTarget);
  Serial2.print("\"");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
  
  Serial2.print("tF1BNextAction.txt=");
  Serial2.print("\"");
  Serial2.print(stringAction(actionKe[urutanKe]));
  Serial2.print("\"");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
  
  while(true){
    nexLoop(nex_listen_list_F1B_Go);
    Usb.Task();
    
    if(Tombol == tSTOP)    return false;
    if(Tombol == tCANCEL)   return false;

    String scanRFID;
    while(true)
    { 
      LetsGOOO(response);

      
      nexLoop(nex_listen_list_F1B_Go);
      Usb.Task();

      if(scanFinished == true){
        scanRFID = scanResult;
        scanFinished = false;
        scanResult = "";
      }
      
      if(Tombol == tSTOP)    return false;
      if(Tombol == tCANCEL)   return false;
      
      switch(typeKe[urutanKe]){
        case typeRFID:
          if(idRFID[urutanKe] == scanRFID && nextTarget == idRFID[urutanKe])
          {
            prevTarget = idRFID[urutanKe];
            actionKe[urutanKe];
            stringAction(actionKe[urutanKe]); // ini untuk tampilan ke serial monitor

            Serial.print(" urutanKe       : ");   Serial.println(urutanKe);
            Serial.print(" prevTarget     : ");   Serial.println(prevTarget);
            Serial.print(" stringAction   : ");   Serial.println(stringAction(actionKe[urutanKe]));

            Serial.print(" nowRFID        : ");   Serial.println(scanRFID);
            Serial.print(" actionKe[]     : ");   Serial.println(actionKe[urutanKe]);
            response = doAction(actionKe[urutanKe]);
            
  
            Serial2.print("tF1BPrevID.txt=");
            Serial2.print("\"");
            Serial2.print(prevTarget);
            Serial2.print("\"");
            Serial2.write(0xff);
            Serial2.write(0xff);
            Serial2.write(0xff);
            
            Serial2.print("tF1BPrevAction.txt=");
            Serial2.print("\"");
            Serial2.print(stringAction(actionKe[urutanKe]));
            Serial2.print("\"");
            Serial2.write(0xff);
            Serial2.write(0xff);
            Serial2.write(0xff);



            // Tempatkan ini di bawah, karena ini increment dari urutanKe, sehingga nextTarget berubah
            nextTarget = idRFID[++urutanKe];
            Serial.print(" nextTarget     : ");   Serial.println(nextTarget);
            Serial.print(" stringAction   : ");   Serial.println(stringAction(actionKe[urutanKe]));

            
            Serial2.print("tF1BNextID.txt=");
            Serial2.print("\"");
            Serial2.print(nextTarget);
            Serial2.print("\"");
            Serial2.write(0xff);
            Serial2.write(0xff);
            Serial2.write(0xff);

            Serial2.print("tF1BNextAction.txt=");
            Serial2.print("\"");
            Serial2.print(stringAction(actionKe[urutanKe]));
            Serial2.print("\"");
            Serial2.write(0xff);
            Serial2.write(0xff);
            Serial2.write(0xff);
          }
          break;
        case typeDI:
//          Serial2.print("tF1BNextID.txt=");
//          Serial2.print("\"");
//          Serial2.print(stringDI(urutanKe));
//          Serial2.print("\"");
//          Serial2.write(0xff);
//          Serial2.write(0xff);
//          Serial2.write(0xff);
          break;
        default:
          break;  
      }


      
    }
  }
}

int pwmKiri, pwmKanan;

void LetsGOOO(int responseLetsGo){
  
  nexLoop(nex_listen_list_F1B_Go);
  if(Tombol == tSTOP)    return false;
  if(Tombol == tCANCEL)   return false;

  if(responseLetsGo == 1){
    pwmKiri = 0;
    pwmKanan = 0;
  }else{
    pwmKiri = 225;
    pwmKanan = 225;
  }

  Serial.print("pwmKiri: ");    Serial.print(pwmKiri);  Serial.print("\t pwmKanan: ");   Serial.println(pwmKanan);
    
}

int doAction(int statusDoAction){
       if(statusDoAction == 0)    return 0;   // kosong
  else if(statusDoAction == 1)    return 1;   // berhenti
  else if(statusDoAction == 2)    return 2;   // maju
  else if(statusDoAction == 3)    {doActionBelokKiri(); return 3;}
  else if(statusDoAction == 4)    return 4;
  else if(statusDoAction == 5)    return 5;
  else if(statusDoAction == 6)    return 6;
  else if(statusDoAction == 7)    return 7;
  else if(statusDoAction == 8)    return 8;
  else if(statusDoAction == 9)    return 9;
  else if(statusDoAction == 10)   return 10;
  else if(statusDoAction == 11)   return 11;
  else if(statusDoAction == 12)   return 12;
  else if(statusDoAction == 13)   return 13;
  else if(statusDoAction == 14)   return 14;
  else if(statusDoAction == 15)   return 15;
  else if(statusDoAction == 16)   return 16;
  else if(statusDoAction == 17)   return 17;
  else if(statusDoAction == 18)   return 18;
  else if(statusDoAction == 19)   return 19;
  else if(statusDoAction == 20)   return 20;
}

void doActionBelokKiri(){
  // pura pura belok kiri
  for(int i = 0; i <= 10; i++){
    Serial2.print("tF1BNextAction.bco=");
    Serial2.print(1500);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
    delay(200);
    Serial2.print("tF1BNextAction.bco=");
    Serial2.print(65504);
    Serial2.write(0xff);
    Serial2.write(0xff);
    Serial2.write(0xff);
    delay(200);
  }
}

