#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

int n;
char test_case[10];

void make_data()
{
    freopen("input.txt","w",stdout);
    for(int i=0;i<1000000;i++){
        int x = rand()%100+1;
        printf("%d ",x);
    }
}

void get_arr(int bubble_arr[], int insertion_arr[], int merge_arr[])
{
    freopen("input.txt","r",stdin);

    for(int i=0;i<n;i++){
        int temp;
        scanf("%d",&temp);
        bubble_arr[i] = insertion_arr[i] = merge_arr[i] = temp;

    }
}

void bubble_sort(int bubble_arr[])
{
    if(test_case[0]=='A') freopen("bubble_sort_avg.txt","a",stdout);
    else if(test_case[0]=='B') freopen("bubble_sort_best.txt","a",stdout);
    else freopen("bubble_sort_worst.txt","a",stdout);

    int i,j;
    clock_t begin = clock();
    for (i=0;i<n-1;i++){
        for (j=0;j<n-i-1;j++){
            if (bubble_arr[j]>bubble_arr[j+1]){     ///swap
                int temp = bubble_arr[j];
                bubble_arr[j] = bubble_arr[j+1];
                bubble_arr[j+1]=temp;
            }
        }
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    time_spent*=1000;       ///second to mili-second
    printf("%d, %.0lf\n",n,time_spent);
}

void insertion_sort(int insertion_arr[])
{
    if(test_case[0]=='A') freopen("insertion_sort_avg.txt","a",stdout);
    else if(test_case[0]=='B') freopen("insertion_sort_best.txt","a",stdout);
    else freopen("insertion_sort_worst.txt","a",stdout);

    int i,j;
    clock_t begin = clock();
    for (i=1;i<n;i++){
        int temp=insertion_arr[i];
        j=i-1;
        while(j>=0 && insertion_arr[j]>temp) {
            insertion_arr[j+1]=insertion_arr[j];
            j--;
        }
        insertion_arr[j+1]=temp;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    time_spent*=1000;       ///second to mili-second
    printf("%d, %.0lf\n",n,time_spent);
}

void merge(int merge_arr[], int begin, int mid, int end)
{
    int i,j,k,left_size,right_size;

    left_size=mid-begin+1;
    right_size=end-mid;

    int left[left_size],right[right_size];

    for(i=0;i<left_size;i++)
        left[i]=merge_arr[i+begin];
    for(i=0;i<right_size;i++)
        right[i]=merge_arr[i+mid+1];

    k = begin;
    i = j = 0;

    while(i<left_size && j<right_size){
        if(left[i]<=right[j]){
            merge_arr[k]=left[i];
            i++;
        }
        else{
            merge_arr[k]=right[j];
            j++;
        }
        k++;
    }

    while(i<left_size){
        merge_arr[k]=left[i];
        i++;
        k++;
    }

    while(j<right_size){
        merge_arr[k]=right[j];
        j++;
        k++;
    }
}

void merge_sort(int merge_arr[], int begin, int end)
{
    if(begin<end){
        int mid = (begin+end)/2;

        merge_sort(merge_arr, begin, mid);
        merge_sort(merge_arr, mid + 1, end);

        merge(merge_arr, begin, mid, end);
    }
}

void primary_merge_func(int merge_arr[])
{
    if(test_case[0]=='A') freopen("merge_sort_avg.txt","a",stdout);
    else if(test_case[0]=='B') freopen("merge_sort_best.txt","a",stdout);
    else freopen("merge_sort_worst.txt","a",stdout);

    clock_t begin = clock();

    merge_sort(merge_arr,0,n-1);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    time_spent*=1000;       ///second to mili-second
    printf("%d, %.0lf\n",n,time_spent);

}

void reverse_arr(int bubble_arr[], int insertion_arr[],int merge_arr[])
{
    int i = 0,j = n - 1;
    while(j >= 0){
        bubble_arr[i] = insertion_arr[j];
        i++;
        j--;
    }
    for(i=0;i<n;i++) insertion_arr[i] = merge_arr[i] = bubble_arr[i];
}

void start_all_func(int bubble_arr[], int insertion_arr[],int merge_arr[])
{
    if(test_case[0]=='W')
        reverse_arr(bubble_arr,insertion_arr,merge_arr);

    primary_merge_func(merge_arr);
    bubble_sort(bubble_arr);
    insertion_sort(insertion_arr);
}

int main()
{
    make_data();

    for(int i=1;i<=100;i++){
        n=i*5000;
        int bubble_arr[n],insertion_arr[n],merge_arr[n];
        get_arr(bubble_arr,insertion_arr,merge_arr);

        char cases[][10] = {"Average","Best","Worst"};

        for(int j=0;j<3;j++){
            strncpy(test_case, cases[j], 10);
            start_all_func(bubble_arr,insertion_arr,merge_arr);
        }
    }

}
