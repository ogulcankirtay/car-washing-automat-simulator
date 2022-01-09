#include <SPI.h>
#include <SD.h>
long randNumber;
int randomSon;

File myFile;
int b = 0;
int butstart = 2; // buton pinlerini atadık
int but2 = 3;
int but3 = 4;
int but4 = 5;
int but5 = 6;
int but6=7; 
int but7=8;
int ledR = A0;
int ledG = A1;
int besAdet,onAdet,yirmiAdet,elliAdet,yuzAdet;
int v[5]; // txtdeki degerleri ayırmak icin virgul indexi dizisi

int bsd;// Buton 1 okunan değerini kaydetmemiz için db1 adında değişken atayoruz...ve diğerleri için
int b2d;
int b3d;
int b4d;
int b5d;
int b6d;
int brd;
int paramiktari=0;
int bittimi=0;
int hzmt1=0;
int hzmt2=0;
int hzmt3=0;
int hzmt4=0;
String tumu;
String str[5];

struct hizmetd
{
    int HizmetId,KalanHizmet,HizmetFiyat;
    //char HizmetAd[15];
    String HizmetAd;
};
  struct hizmetd hizmet[4];

void setup(){
    
    Serial.begin(9600);
    randomSeed(analogRead(A0));
 pinMode(butstart , INPUT); // Buton pinlerini giris olarak atadik
  pinMode(but2 , INPUT);
  pinMode(but3 , INPUT);
  pinMode(but4 , INPUT);
  pinMode(but5 , INPUT);
  pinMode(but6 , INPUT);
  pinMode(ledR , OUTPUT); 
  pinMode(ledG , OUTPUT); 
   
  while (!Serial) {
    ; 
  }
 
  Serial.println("Arac Yikama Makinesine Hosgeldiniz");
 
  if (!SD.begin(10)) {
    Serial.println("SD Kart Acilamadi");
    while (1);
  }
  Serial.println("Dosya basariyla acildi.");

  myFile = SD.open("hizmet.txt",FILE_READ);
  if (myFile) {
    //Serial.println("hizmet.txt:");

    if (myFile.available()) { 
      //Serial.write(myFile.readStringUntil("\n"));
      //Serial.println(myFile.readString());
      tumu= myFile.readString();
    }
    
    myFile.close();
  } else {
    Serial.println("Txt dosyasi acilirken hata olustu.");
  }
  
  v[0] = tumu.indexOf('.'); v[1] = tumu.indexOf('.',v[0]+1);
  v[2] = tumu.indexOf('.',v[1]+1); v[3] = tumu.indexOf('.',v[2]+1); v[4]=tumu.indexOf('.',v[3]+1);
  
  str[0] = tumu.substring(0,v[0]);     // Satir 1
  str[1] = tumu.substring(v[0]+2,v[1]);// Satir 2
  str[2] = tumu.substring(v[1]+2,v[2]);// Satir 3
  str[3] = tumu.substring(v[2]+2,v[3]);// Satir 4
  str[4] = tumu.substring(v[3]+2,v[4]);// Satir 5
  
  for(int i=0; i<5; i++){ // dosyadan okunan degerlerin degiskenlere atanma islemi

    if(i==0){
      v[0] = str[0].indexOf(','); v[1] = str[0].indexOf(',',v[0]+1);
      v[2] = str[0].indexOf(',',v[1]+1); v[3] = str[0].indexOf(',',v[2]+1);
      besAdet = str[0].substring(0,v[0]).toInt();
      onAdet = str[0].substring(v[0]+1,v[1]).toInt();
      yirmiAdet = str[0].substring(v[1]+1,v[2] ).toInt();
      elliAdet = str[0].substring(v[2]+1,v[3]).toInt();
      yuzAdet = str[0].substring(v[3]+1,str[0].length()).toInt();
    }
    else{
      v[0] = str[i].indexOf(','); v[1] = str[i].indexOf(',',v[0]+1); v[2] = str[i].indexOf(',',v[1]+1);
      hizmet[i-1].HizmetId = str[i].substring(0,v[0]).toInt();
      hizmet[i-1].HizmetAd = str[i].substring(v[0]+1,v[1]);
      hizmet[i-1].KalanHizmet = str[i].substring(v[1]+1,v[2]).toInt();
      hizmet[i-1].HizmetFiyat = str[i].substring(v[2]+1,str[i].length()).toInt();
    }
    
  }

}
void loop(){  

    bsd = digitalRead(butstart);  // butonları oku ve durum bilgilerini değişkenlere kaydet
  b2d = digitalRead(but2);
  b3d = digitalRead(but3);
  b4d = digitalRead(but4);
  b5d = digitalRead(but5);
  b6d = digitalRead(but6); 
  brd = digitalRead(but7); 

    randNumber = random(4)+1;
    randNumber;
    delay(20);
    //Serial.print("RandomNUmber:");
    //Serial.println(randNumber);
    
  
if (bsd == HIGH ) // b1d HIGH ise ( bu bağlantıda 1. butona basılmış ise)
   {
  if(bittimi==0){
  paramiktari+=5;
  delay(500);
  Serial.println(paramiktari); 
 }
  else if(paramiktari>=15 && hizmet[0].KalanHizmet>0) {
    delay(500);
    //hizmet[0].kalanhizmet-=1;
  Serial.println("kopukleme");
    //paramiktari-=hizmet[0].HizmetFiyat;
  paramiktari-=15;
    hizmet[0].KalanHizmet--;
    hzmt1++;
  
  }
  else if(paramiktari<15 ) {
    delay(500);
  Serial.println("yetersiz bakiye");
  Serial.println("para eklemek icin ekle butonunua basiniz");
  }
  else{
    Serial.println("yetersiz islem");
    }
}
  if (b2d == HIGH)  // b1d HIGH değil, b2d HIGH ise ( yani 2. butona basılmış ise)
  {
    if(bittimi==0){
 paramiktari+=10;
  delay(500);
  Serial.println(paramiktari);
    }
    else if(paramiktari>=10 && hizmet[1].KalanHizmet>0) {
    delay(500);
    //hizmet[1].kalanhizmet-=1;
  Serial.println("yikama");
    //paramiktari-=hizmet[1].HizmetFiyat;
  paramiktari-=10;
      hizmet[1].KalanHizmet--;  
      hzmt2++;
  
  }
  else if(paramiktari<10) {
    delay(500);
  Serial.println("yetersiz bakiye");
  Serial.println("para eklemek icin ekle butonunua basiniz");
  }
   else{
    Serial.println("yetersiz islem");
    }
}
  
  
  if (b3d == HIGH)      //3. butona basılmı ise
  {
    if(bittimi==0){
   paramiktari+=20;
  delay(500);
  Serial.println(paramiktari);
    } 
  
    else if(paramiktari>=5 && hizmet[2].KalanHizmet>0) {
    delay(500);
    //hizmet[2].kalanhizmet-=1;
  Serial.println("kurulama");
    //paramiktari-=hizmet[2].HizmetFiyat;
  paramiktari-=5;
         hizmet[2].KalanHizmet--;
      hzmt3++;
  }
      else if(paramiktari<5) {
    delay(500);
  Serial.println("yetersiz bakiye");
  Serial.println("para eklemek icin ekle butonunua basiniz");
  }
   else{
    Serial.println("yetersiz islem");
    } 
  }
   if (b4d == HIGH)        // 4. butona basılmış ise
  {
     if(bittimi==0){
paramiktari+=50;
  delay(500);
  Serial.println(paramiktari);
     }
     else if(paramiktari>=50 && hizmet[3].KalanHizmet>0) {
    delay(500);
    //hizmet[3].kalanhizmet-=1;
  Serial.println("cilalama");
    //paramiktari-=hizmet[3].HizmetFiyat;
  paramiktari-=50;
     hizmet[3].KalanHizmet--;
       hzmt4++;
     }
  else if(paramiktari<50){
    delay(500);
  Serial.println("yetersiz bakiye");
   Serial.println("para eklemek icin ekle butonunua basiniz");
  }
   else{
    Serial.println("yetersiz islem");
    }   
   }
  if (b5d == HIGH)        // 5. butona basılmış ise
  {
    delay(500);
    if(bittimi==0){
    paramiktari+=100;
   Serial.println(paramiktari);
    }
    else if(bittimi==1){
      bittimi=0;
      Serial.println("para ekleyiniz..");
      }
    }
   if (b6d == HIGH) // .6. buton bitir       
  { 
    
     if(bittimi==1){
      
      randomSon = randNumber;
      //Serial.println(randomSon);
      if(randomSon == 2){
        Serial.println("PARA SIKISTI");
        digitalWrite(ledR,HIGH);
        paramiktari=0;
        bittimi=0;
        Serial.println("Paraniz geri iade edildi.");
        delay(3000);
        digitalWrite(ledR,LOW);
        
      }
      else{
        digitalWrite(ledG,HIGH);

        
      Serial.print(paramiktari); 
      Serial.println(" TL para ustu verilecek");
      
    while(paramiktari>=100 & yuzAdet>0){
      paramiktari-=100;
      Serial.println("100 TL");
      
      yuzAdet-=1;
      
      }
         while(paramiktari>=50 & elliAdet>0){
         
      paramiktari-=50;
      Serial.println("50 TL");
      elliAdet-=1;
      }
         while(paramiktari>=20 & yirmiAdet>0){
      paramiktari-=20;
      Serial.println("20 TL");
      yirmiAdet-=1;
      }
         while(paramiktari>=10 & onAdet>0){
      paramiktari-=10;
      Serial.println("10 TL");
      onAdet-=1;
      }
           while(paramiktari>=5 & besAdet>0){
      paramiktari-=5;
      Serial.println("5 TL");
      besAdet-=1;
      }
      if(paramiktari>0){
        Serial.println("Kasada yeterli para yoktur");
        }
        delay(300);
        digitalWrite(ledG,LOW);
        Serial.print("Adetler--> 5Lira:"); Serial.print(besAdet); Serial.print(" 10Lira:"); Serial.print(onAdet);
        Serial.print(" 20Lira:"); Serial.println(yirmiAdet); Serial.print("50Lira:"); Serial.print(elliAdet);
        Serial.print(" 100Lira:"); Serial.print(yuzAdet); Serial.print("  ");
      }
      }
      else{
        bittimi = 1;
      }
     delay(500); 
  } 
   if (brd == HIGH) // .7. buton reset       
  {
delay(500);
  Serial.println("reset");
  if(randomSon != 2){
     paramiktari+=(15*hzmt1);
     paramiktari+=(10*hzmt2);
     paramiktari+=(5*hzmt3);
     paramiktari+=(50*hzmt4);
  }

   hizmet[0].KalanHizmet+=hzmt1;
    hizmet[1].KalanHizmet+=hzmt2;
    hizmet[2].KalanHizmet+=hzmt3;
    hizmet[3].KalanHizmet+=hzmt4;  
     hzmt1=0;
     hzmt2=0;
     hzmt3=0;
     hzmt4=0;
     
      Serial.println(paramiktari);
  }
  

}
