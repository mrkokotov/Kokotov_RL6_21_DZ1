#include <cmath>
#include <fstream>
#include <QDebug>
#include <iostream>
#include <iomanip>
#include <set>
#include <QCoreApplication>
#include <cstdlib>
#include <time.h>
#include <DzSorts.h>
using namespace std;
int* rand_el(int* arr,int size_arr){ //Заполнение массива случайными элементами
    arr = new int[size_arr];
    srand(time(NULL));
    for (int i = 0; i < size_arr; i++)
    {
        arr[i] = rand() % 1000;
    }
    return arr;
}
//сортировки//
void sort1(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1])
                    swap(arr[j],arr[j+1]);
        }
    }
}//Сортировка пузырьком
void sort2(int* arr, int size) {
    int Left, Right;
    Left=1;
    Right=size-1;
//    qDebug()<<"check1";
    while (Left<=Right)
    {
        for (int i=Right; i>=Left; i--)
            if (arr[i-1]>arr[i]) swap(arr[i-1],arr[i]);
        Left++;
        for (int i=Left; i<=Right; i++)
            if (arr[i-1]>arr[i]) swap(arr[i-1],arr[i]);
        Right--;
    }
//    qDebug()<<"check2";
}//Сортировка перемешиванием
void sort3(int* arr, int size) {
    int key=0, temp=0;
    for (int i=0; i<size-1; i++)
    {
    key=i+1;
    temp=arr[key];
    for (int j=i+1; j>0; j--)
    {
    if (temp<arr[j-1])
    {
    arr[j]=arr[j-1];
    key=j-1;
    }
    }
    arr[key]=temp;
    }
}//Cортровка вставками
void sort4(int* arr, int size) {
    for(int s = size / 2; s > 0; s /= 2)
       for(int i = 0; i < size; i++)
         for(int j = i + s; j < size; j += s)
             if(arr[i] > arr[j])
                swap(arr[i], arr[j]);
}//Сортировка Шэлла
void merge(int *merged, int *L, int lenL, int *R, int lenR){
  int i = 0;
  int j = 0;
  while(i<lenL||j<lenR){
    if (i<lenL & j<lenR){
      if(L[i]<=R[j]){
        merged[i+j] = L[i];
        i++;
      }
      else{
        merged[i+j] = R[j];
        j++;
      }
    }
    else if(i<lenL){
      merged[i+j] = L[i];
      i++;
    }
    else if(j<lenR){
      merged[i+j] = R[j];
      j++;
    }
  }
}
void sort5(int* arr, int size) {
      if(size>1){
        int middle = size/2;
        int rem = size-middle;
        int* L = new int[middle];
        int* R = new int[rem];
        for(int i=0;i<size;i++){
          if(i<middle){
            L[i] = arr[i];
          }
          else{
            R[i-middle] = arr[i];
          }
        }
        sort5(L,middle);
        sort5(R,rem);
        merge(arr, L, middle, R, rem);
      }
}//Сортировка слиянием
void sort6(int* arr, int size) {
    int count, key;
    for (int i=0; i<size-1; i++)
    {
    count=arr[i]; key=i;
    for (int j=i+1; j<size; j++)
    if (arr[j]<arr[key]) key=j;
    if (key!=i)
    {
    arr[i]=arr[key];
    arr[key]=count;
    }
    }
}//Сортировка выбором
void sort7(int* arr, int size) {
    int mid;
    int f=0, l=size-1;
    mid=arr[(f+l) / 2]; //нахождение опорного элемента
    do
    {
    while (arr[f]<mid) f++;
    while (arr[l]>mid) l--;
    if (f<=l)
    {
    swap(arr[f],arr[l]);
    f++;
    l--;
    }
    } while (f<l);
    if (0<l) sort7(arr, l);
    if (f<(size-1)) sort7(arr+f, size-f);
}//Быстрая сортировка
void (*pSort[7]) (int*,int)={sort1,sort2,sort3,sort4,sort5,sort6,sort7};
float getTimeSort(void (*pSort)(int*,int),int size)
{
    float time1;
    int* mass;
//    qDebug()<<"f1 ";
    mass=rand_el(mass,size);
//    mass = new int[size];
//    for (int i = 0; i < size; i++)
//    {
//        qDebug()<<i<<" "<<mass[i];
//    }
//    qDebug()<<"f1 ";
    clock_t t1=clock();
//    qDebug()<<"c1 ";
    pSort(mass,size);
//    for (int i = 0; i < size; i++)
//    {
//        qDebug()<<i<<" "<<mass[i];
//    }
//    qDebug()<<"c2 ";
    clock_t t2=clock()-t1;
//    qDebug()<<"t2";
    delete[]mass;
//    qDebug()<<"t4";
    //if(((float)t1 / CLOCKS_PER_SEC)>10)//
    time1=((float)t2 / CLOCKS_PER_SEC);
//    qDebug()<<"t3";
    return time1;
}
void sborka()
{
    ofstream out;
    out.open("TestSorts.txt");
    if(!out.is_open())
    {
        return;
    }
    int x=1;
    int a=0;
    bool flag[7]={true,true,true,true,true,true,true};
    float time;
    for(long int size=1000;size<10000000;size+=x*1000)
    {
        qDebug()<<"size "<<size;
        a++;
        if(a==10){
            a=1;
            x*=10;
        }
        //qDebug()<<"size1 "<<size;
//        out<<std::fixed<<std::setprecision(8) << size<<'\t';
        out<<size<<'\t';
        //qDebug()<<"size2 "<<size;
        for(int i=0;i<7;i++)
        {
            qDebug()<<"i "<<i;
            if(flag[i])
            {
//                qDebug()<<"i1 ";
                time=getTimeSort(pSort[i],size);
//                qDebug()<<"i2 ";
                //time=(float)getTimeSort(pSort[i],size)/CLOCKS_PER_SEC;
                if(time>10)
                {
                    flag[i]=false;
                    out<<"10"<<'\t';
                }
                else
                {
                    qDebug()<<"time "<<time;
                    out<<time<<'\t';
                }
            }
            else
            {
                out<<"10"<<'\t';
            }
        }
        out<<'\n';
    }
    out.close();
}
