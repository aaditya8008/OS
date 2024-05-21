#include <stdio.h>

void insert(int data,int idx,int size,int arr[]){
    if(idx<size&&idx>=0){
int prev=data;
int next=arr[idx];
for(int i=idx;i<size;i++){
arr[i]=prev;
prev=next;
next=arr[i+1];
}
    }
    else{
        printf("Index Out Of Bounds\n");
    }
}
void pr(int size,int arr[]){
   for(int i=0;i<size;i++){
    printf("%d ",arr[i]);
   }
   printf("\n");
}

int main() {
  
int arr[10];
 int size=10;
  for(int i=0;i<size;i++){
     arr[i]=rand()%999+1;
  }
  pr(size,arr);
printf("After Insertion:\n");
     insert(12,1,size,arr);
      pr(size,arr);

    return 0;
}