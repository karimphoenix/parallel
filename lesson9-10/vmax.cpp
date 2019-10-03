#include <vector>
#include <pthread.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <stdio.h>
#include <errno.h>
#include <cmath>

using namespace std;

vector <int> VecSearch;

vector <int> VecRes;

typedef struct VectPart{

    vector<int> PartV;
    int curent_thread;

}VPart;

void* SearchMax(void * argarr)
{
    VPart * VP = (VPart*)argarr;

    vector<int>::iterator ItMax;

    ItMax = max_element(VP->PartV.begin(), VP->PartV.end());

    VecRes[VP->curent_thread]=*ItMax;

    return NULL;

}

int main (int  argnum, char ** args)
{

    pthread_t* threads;
    VPart *PartsVect;
    int status;
    void* status_addr;

    int ptr, elements, dd;
    ptr=atoi(args[2]);

    elements=atoi(args[1]);

    dd=elements/ptr;
    cout<<ptr<<"\t"<<elements<<"\t"<<dd<<endl;
    //memory for structure
    if ((PartsVect = new VPart[dd]) == NULL)
    {
        printf("SegFault\n");
        exit(1);
    }

    //memory for threads
    if (( threads = new pthread_t[ptr]) == NULL)
    {
        printf("SegFaultPTR\n");
        exit(1);
    }

    VecSearch.resize(elements);
    VecRes.resize(ptr);
    int i,j,k;

    for(i=0;i<elements;i++)
    VecSearch[i]=rand()%100;

    for(i=0;i<ptr;i++)
        PartsVect[i].PartV.resize(dd);

    int dl;
    dl=elements%ptr;
    cout<<dl<<endl;

    for (i=0; i<elements;i++)
        cout<<VecSearch[i]<<" ";
        cout<<endl;

    PartsVect[0].PartV.resize(dd+dl);

    for (j=0;j<dl+dd;j++)
    {
        PartsVect[0].PartV[j]=VecSearch[j];
        cout<<PartsVect[0].PartV[j]<<" ";
    }
    cout<<endl;

    for(i=1;i<ptr;i++)
    {
        k=i*dd+dl;
        cout<<k<<endl;
        for(j=0;j<dd;j++)
        {
            PartsVect[i].PartV[j]=VecSearch[j+k];
            cout<<PartsVect[i].PartV[j]<<" ";

        }
     }
    cout<<endl;

    //create threads
    for (i=0;i<ptr;i++)
    {
        status=pthread_create(&threads[i], NULL, SearchMax, (void*)(PartsVect+i));
        if (status!=0){
        exit(-1);
        }
     }
    //int ik;
     //lock threads
     for(i=0;i<ptr;i++)
     {
        status = pthread_join(threads[i], (void**)&status_addr);
        switch (status){
        case 0:/*cout<<"allnormal"<<endl;*/ break;
        case EINVAL:cout<<"EINVAL"<<endl; break;
        case EDEADLK:cout<<"EDEADLK"<<endl; break;
        case ESRCH:cout<<"ESRCH"<<endl; break;
        default:{
        cout<<status<<"\t"<<"\t"<<ESRCH<<"\t"<<EINVAL<<"\t"<<EDEADLK<<endl;
        perror("ptr-join\n");
        exit(-2);}
        }
      }

      cout<<endl;

      cout<<"Result\t"<<*max_element(VecRes.begin(),VecRes.end())<<endl;

      return 0;
 }
