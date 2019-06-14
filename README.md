# CHINESE POSTAN PROBLEM 

## How to run
本次作業為解連通、無向，無權重之圖形
* Input files 
    * ex: topo.txt
* Linux
    ```
    $ make 
    $ ./main.out
    ```
* Output files
    * .dot (plot.dot in default)
    * .txt (postman_path.txt in default)
* Modify files

  可以在 main.cc 的define中修改輸入/輸出.txt檔之檔名

    `#define INPUT "topo"`
    `#define OUTPUT "postman_path"`
    
## 解題邏輯    
1. 找出圖上所有odd vertex
2. 將odd vertex以最短路徑兩兩相連，使全部的vertex為even vertex
3. 利用新的路線找Euler Path，即得中國郵差路徑
        
## 程式碼實作
   1. 將拓樸輸入後，計算此圖形每個vertex的degree
   2. 尋找odd vertex並記錄
   3. 為了要尋找最短路徑，使用Dijkstra's Algorithm，因此建立adjacent matrix，同時記錄edge的個數
   4. 如果是odd vertex，則利用Dijkstra's Algorithm尋找兩兩odd vertex的最短路徑，並相連。同時更新adjacent matrix以及edge的個數
   5. 尋找郵差路徑。現在所有vertex的degree都是偶數，因此一定是Euler Circuit，只要比對edge的個數以及行走路徑的距離是否一樣，便能確定是否每條edge都走過。
