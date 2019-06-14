# CHINESE POSTMAN PROBLEM 

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
   3. 利用更新的地圖找中國郵差路徑
        
## 程式碼實作
   1. 將拓樸輸入node_name後，計算此圖形每個vertex的degree
   2. 尋找odd vertex並記錄，同時選擇一vertex為起點
   3. 為了要尋找最短路徑，使用Dijkstra's Algorithm，因此建立adjacent matrix，同時記錄edge的個數 **(使用函式dikjstra)**
   4. 如果是odd vertex，則利用Dijkstra's Algorithm尋找兩兩odd vertex的最短路徑，並將此路徑connect於node_name。同時更新adjacent matrix以及edge的個數 **(使用函式addpath)**
   5. 尋找郵差路徑。現在所有vertex的degree都是偶數，因此一定是Euler Circuit，只要比對edge的個數以及行走路徑的距離是否一樣，便能確定是否每條edge都走過，走過的路徑會在adjacent map扣除，最後清空adjacent map。 **(使用函式findcircuit)**
   
## 函式解釋
* dikjstra

   此演算法為求兩點之最短路徑。利用adjacent matrix從指定起點開始搜尋，如果有發現更短的路徑，便會更新目前路徑，最後可以導出每一點與起點的最短路徑關係。
* addpath

   這個function前提是已經由 dikjstra 找到最短路徑。從終點不斷往回搜尋到起點，同時將這一路上經過的路徑加一條edge
* findcircuit

   當新的edge都添加完畢後，便訓找如何經過所有的edge的路線。先搜尋與該vertex相連的edges，與其中之一相連，刪去adjacent matrix的對應位置並遞迴搜尋，直到終點vertex沒有edge可以相連為止。經由比較行走距離是否和node_name中的edges相等，若不相等，則代表此路徑並非完整走過每條edge，因此將重新搜尋，直到相等

## 執行結果
* 輸入檔案topo.txt
   圖形表示：

![image](https://github.com/claireyy23/graph_theory/blob/master/%E6%8A%95%E5%BD%B1%E7%89%871.JPG)
* 輸出檔案
   * postman_path.txt
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/txt%E8%BC%B8%E5%87%BA.JPG)
   * path.dot轉成png檔
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/%E6%8A%95%E5%BD%B1%E7%89%872.JPG)
      
* 終端機
   1. 計算vertex個數、搜尋每個vertex的degree、紀錄odd degree
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_vertex.JPG)
      
   2. 建立adjacent matrix  
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_inimap.JPG)
      
   3. 將odd vertex依照最短路徑連edges
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_addpath.JPG)
      
   4. 更新adjacent matrix
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_newmap.JPG)
      
   5. 輸出path
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_path.JPG)
      
   6. 清空後的adjacent matrix
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_finalmap.JPG)
      
      
      
