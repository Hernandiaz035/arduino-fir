const float a[]={0.000072967536794644,0.000290964740761179,0.000435995814441981,0.000290964740768285,0.000072967536790758},//{0.0004,0.0017,0.0025,0.0017,0.0004},
        b[]={1,-3.701774464251717,5.225330977095858,-3.330141680387448,0.808050380938323};//{1,-3.1806,3.8612,-2.1122,0.4383};
const char orden=(sizeof(a)/sizeof(a[0]))-1,
      k=2;
volatile float p[2][orden],
        x,
        y;
String inputString="";
char sz[10];

int last=0;
const int delta=10;
const float Tm=0.01;
volatile float t=0;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  processed=true;
}

void loop() {
  if ((millis() - last >= delta)) {
    t += Tm;
    x = sin(150*t)+sin(10*t)+sin(80*t)+sin(15*t)+sin(100*t)+sin(20*t)+sin(90*t);
    y = a[0]*x+p[0][0];   //yk(i)=a(1)*yt(i)+p(1,k-1);
    p[1][orden-1] = a[orden]*x-b[orden]*y;   //p(orden,k)=a(orden+1)*yt(i)-b(orden+1)*yk(i);
    for(int iorden = 0 ; iorden < orden - 1 ; iorden++) {
      p[1][iorden] = p[0][iorden+1]+a[iorden+1]*x-b[iorden+1]*y;   //p(iorden,k)=p(iorden+1,k-1)+a(iorden+1)*yt(i)-b(iorden+1)*yk(i);
    }
    for(int iorden = 0 ; iorden < orden ; iorden++) {
      p[0][iorden] = p[1][iorden];
    }
    Serial.println(y);
    processed = true;
    last = millis();
  }
}
