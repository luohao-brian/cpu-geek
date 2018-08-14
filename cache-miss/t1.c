
#define NUM 393216
 
int main(){
    float a[NUM],b[NUM];
    int i;
    for(i=0;i<1000;i++)
        add(a,b,NUM);
}
 
int add(int *a,int *b,int num){
    int i=0;
    for(i=0;i<num;i++){
        *a=*a+*b;
        a++;
        b++;
    }   
}

