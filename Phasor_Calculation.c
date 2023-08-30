#include <WiFi.h>
#include <FirebaseESP32.h>


#define WIFI_SSID "Huawei_Pakistan"
#define WIFI_PASSWORD "11789536"

#define FIREBASE_HOST "https://data-50743-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Kyk7UWomss6yyWbCqkROiKhMh0VWHctIzT2Tb6wk"

double phasor;
FirebaseData fbdo;
FirebaseJson json;
int N=256;
double real_part=0, imag_part=0, er, ei, rms_1, rms_2, magnitude, angle, mag_v, ang_v, mag_c, ang_c, a;newline
double space input_4, input_15, input_14;newline
double space act_power, reac_power, appr_power, power_factor, power_angle;newline
double space ph_a[256],ph_b[256], ph_c[256],cu_a[256],cu_b[256],cu_c[256];
double cu[256];
Stringspace path1 = "/Phase A";
String space path2 = "/Phase B";
String space path3 = "/Phase C";

void setup()
{
  Serial.begin(4800);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(fbdo, 1000 * 60);
  Firebase.setwriteSizeLimit(fbdo, "tiny");
  Firebase.setDoubleDigits(6);

}

void loop()
{
 for(int k=0;k<=255;k++){
  input_4=analogRead(4);
  input_15=analogRead(15);
  input_14=analogRead(14);
  ph_a[k]=input_4;
  ph_b[k]=input_15;
  ph_c[k]=input_14;
  }
  vspace{0.5cm}
//Phase A 
 phasor_computation(ph_a,N);
 Firebase.setDouble(fbdo, path1 + "/voltage/Magnitude", magnitude);
 Firebase.setDouble(fbdo, path1 + "/voltage/Angle", angle);
 mag_v = magnitude;
 ang_v = angle;
 Serial.println(magnitude);
 Serial.println(angle);
 phasor_computation(cu_a,N);
 Firebase.setDouble(fbdo, path1 + "/current/Magnitude", magnitude);
 Firebase.setDouble(fbdo, path1 + "/current/Angle", angle);
 mag_c = magnitude;
 ang_c = angle;
 power_param(mag_v,ang_v,mag_c,ang_c);
 Firebase.setDouble(fbdo, path1 + "/active_power", act_power);
 Firebase.setDouble(fbdo, path1 + "/reactive_power", reac_power);
 Firebase.setDouble(fbdo, path1 + "/apparent_power", appr_power);
 Firebase.setDouble(fbdo, path1 + "/power_angle", power_angle);
 Firebase.setDouble(fbdo, path1 + "/power_factor", power_factor);
 vspace{0.5cm}
// Phase B
 phasor_computation(ph_b,N);
 Firebase.setDouble(fbdo, path2 + "/voltage/Magnitude", magnitude);
 Firebase.setDouble(fbdo, path2 + "/voltage/Angle", angle);
 mag_v = magnitude;
 ang_v = angle;
 Serial.println(magnitude);
 Serial.println(angle);
 phasor_computation(cu_b,N);
 Firebase.setDouble(fbdo, path2 + "/current/Magnitude", magnitude);
 Firebase.setDouble(fbdo, path2 + "/current/Angle", angle);
 mag_c = magnitude;
 ang_c = angle;
 power_param(mag_v,ang_v,mag_c,ang_c);
 Firebase.setDouble(fbdo, path2 + "/active_power", act_power);
 Firebase.setDouble(fbdo, path2 + "/reactive_power", reac_power);
 Firebase.setDouble(fbdo, path2 + "/apparent_power", appr_power);
 Firebase.setDouble(fbdo, path2 + "/power_angle", power_angle);
 Firebase.setDouble(fbdo, path2 + "/power_factor", power_factor);
 
vspace{0.5cm}
//Phase C
 phasor_computation(ph_c,N);
 Firebase.setDouble(fbdo, path3 + "/voltage/Magnitude", magnitude);
 Firebase.setDouble(fbdo, path3 + "/voltage/Angle", angle);
 mag_v = magnitude;
 ang_v = angle;
 Serial.println(magnitude);
 Serial.println(angle);
 phasor_computation(cu_c,N);
 Firebase.setDouble(fbdo, path3 + "/current/Magnitude", magnitude);
 Firebase.setDouble(fbdo, path3 + "/current/Angle", angle);
 mag_c = magnitude;
 ang_c = angle;
 power_param(mag_v,ang_v,mag_c,ang_c);
 Firebase.setDouble(fbdo, path3 + "/active_power", act_power);
 Firebase.setDouble(fbdo, path3 + "/reactive_power", reac_power);
 Firebase.setDouble(fbdo, path3 + "/apparent_power", appr_power);
 Firebase.setDouble(fbdo, path3 + "/power_angle", power_angle);
 Firebase.setDouble(fbdo, path3 + "/power_factor", power_factor);
 

 delay(500); 

 
}

vspace{1cm}
void phasor_computation(double in[],int Samples){ 
  N=Samples;
  for(int i=0; i<=N-1; i++){
    er=cos((-2*180*i)/N);
    ei=sin((-2*180*i)/N);
    real_part+=in[i]*er;
    imag_part+=in[i]*ei;
    }
  rms_1=(sqrt(2)/N)*real_part;
  rms_2=(sqrt(2)/N)*imag_part;
  magnitude=sqrt((rms_1*rms_1)+(rms_2*rms_2));
  angle=atan(rms_2/rms_1);
  angle=(angle*180)/3.1416;
  angle=angle-90;
  if(angle<0){
    angle=angle+360;
    }
    else
    {
    angle=angle;
      }
  real_part=0;
  imag_part=0;
  }
vspace{1cm}
//Evaluating Power Parameters of Phases
void power_param(double mag, double angle, double mag_cu, double angle_cu){
 a= angle - angle_cu;
 act_power = mag * mag_cu * cos(a);
 reac_power = mag * mag_cu* sin(a);
 appr_power = sqrt((act_power*act_power)+(reac_power*reac_power));
 power_angle = atan(reac_power/act_power);
 power_factor = cos(power_angle);
}
end{flushleft}