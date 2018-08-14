#define NUM 39216
typedef struct{
    float a;
    float b;
}Array;
 
int main(){
    Array myarray[NUM];
    int j=0;
    for(j=0;j<1000;j++)
        add(myarray,NUM);
}
 
int add(Array *myarray,int num){
    int i=0;
    for(i=0;i<num;i++){
        myarray->a=myarray->a+myarray->b;
        myarray++;
    }   
}
