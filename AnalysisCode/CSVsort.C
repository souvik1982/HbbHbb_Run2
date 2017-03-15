
double singleCSV(float x) {
   //float value = -0.192834+4.02025*pow(x,1)+-11.8859*pow(x,2)+14.9736*pow(x,3)+-5.93882*pow(x,4);
   //float value = -0.5831 +7.264*pow(x,1)+-21.45*pow(x,2)+26.74*pow(x,3)+-11.01*pow(x,4); //RunB-F
   float value = -0.5048 +6.592*pow(x,1)+-18.57*pow(x,2)+22.75*pow(x,3)+-9.3*pow(x,4); // RunG-H
   if(value>1) value = 1;
   if(value<0) value = 0;
   return value;
//    return -0.192834+4.43014*pow(x,1)-11.8859*pow(x,2)+14.9736*pow(x,3)-5.93882*pow(x,4);
//    return -5.93882+14.9736*pow(x,1)-11.8859*pow(x,2)+4.43014*pow(x,3)+-0.192834*pow(x,4);
}

double CSVn(int n, float x, float y, float z, float w) {
   float c0Y = singleCSV(x);
   float c1Y = singleCSV(y);
   float c2Y = singleCSV(z);
   float c3Y = singleCSV(w);
       float c0N = 1-singleCSV(x);
   float c1N = 1-singleCSV(y);
   float c2N = 1-singleCSV(z);
   float c3N = 1-singleCSV(w);

   float value = 0;
       //
   if(n<=4){
       value += c0Y * c1Y * c2Y * c3Y;
   }

   if(n<=3){
       value += c0N * c1Y * c2Y * c3Y;
       value += c0Y * c1N * c2Y * c3Y;
       value += c0Y * c1Y * c2N * c3Y;
       value += c0Y * c1Y * c2Y * c3N;
   }

   if(n<=2){
       value += c0N * c1N * c2Y * c3Y;
       value += c0N * c1Y * c2N * c3Y;
       value += c0N * c1Y * c2Y * c3N;
       value += c0Y * c1N * c2N * c3Y;
       value += c0Y * c1N * c2Y * c3N;
       value += c0Y * c1Y * c2N * c3N;
   }

   if(n<=1){
       value += c0Y * c1N * c2N * c3N;
       value += c0N * c1Y * c2N * c3N;
       value += c0N * c1N * c2Y * c3N;
       value += c0N * c1N * c2N * c3Y;
   }

   if(n<=0){
       value += c0N * c1N * c2N * c3N;
   }

   return value;
}

double CSVn(int n, float x, float y) {
   float c0Y = singleCSV(x);
   float c1Y = singleCSV(y);
       float c0N = 1-singleCSV(x);
   float c1N = 1-singleCSV(y);

   float value = 0;
       //
   if(n<=2){
       value += c0Y * c1Y;
   }

   if(n<=1){
       value += c0N * c1Y;
       value += c0Y * c1N;
   }

   if(n<=0){
       value += c0N * c1N;
   }

   return value;
}

