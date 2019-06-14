# CHINESE POSTMAN PROBLEM 

## 問題描述
中國郵差問題，與七橋問題相似，要求在最短的路徑下，經過所有的邊。 在一個無向圖中，找到一個最短的封閉路徑，且此路徑需通過所有邊至少一次

## 專案描述
本專案為解無向，權重為1之圖形
## 執行方法
* 輸入檔案
    * ex: topo.txt
* Linux
    ```
    $ make 
    $ ./main.out
    ```
* 輸出檔案
    * .dot (plot.dot in default)
    * .txt (postman_path.txt in default)
* 如何修改檔案

  可以在 main.cc 的define中修改輸入/輸出.txt檔之檔名

    `#define INPUT "topo"`
    `#define OUTPUT "postman_path"`
    
## 解題邏輯    
   1. 確認圖是否connected
   2. 找出圖上所有odd vertex
   3. 將odd vertex以最短路徑兩兩相連，使全部的vertex為even vertex
   4. 更新的地圖已為Euler circuit，尋找走遍每個edge的路徑
        
## 程式碼實作
   1. 將拓樸輸入`node_name`後，計算此圖形每個vertex的degree
   2. 尋找odd vertex並記錄，同時選擇一vertex為起點
   3. 為了要尋找最短路徑，使用Dijkstra's Algorithm，因此建立adjacent matrix `map`，同時記錄edge的個數 
   4. 利用 `map`，判斷此圖是否為connected graph，若不是，則結束程式 **(使用函式connect)**
   5. 如果是odd vertex，則利用Dijkstra's Algorithm尋找兩兩odd vertex的最短路徑，並將此路徑connect於`node_name`。同時更新`map`以及edge的個數 **(使用函式dikjstra,addpath)**
   6. 尋找郵差路徑。現在所有vertex的degree都是偶數，因此一定是Euler Circuit，只要比對edge的個數以及行走路徑的距離是否一樣，便能確定是否每條edge都走過，走過的路徑會在`map`扣除，最後清空`map`  **(使用函式findcircuit)**
   
## 函式解釋
* connect

   此函式會將可經過的edge判定為connected。如果此圖為connected graph，勢必任選一點可以抵達任何一點；反之任選一點而有達不到的另一點則必不connected。利用 `map`，以第一個被輸入的vertex設為起點，利用遞迴的方式去更新`connected[]`的狀態
* dikjstra

   此演算法為求兩點之最短路徑。利用 `map`從指定起點開始搜尋，以`visit`來判斷此vertex是否被執行過。如果有發現更短的路徑，便會更新目前路徑長度，並記錄其`parent`，最後可以導出每一點與起點的最短路徑關係
* addpath

   在使用這個function前提是已經由 dikjstra 找到最短路徑。從終點不斷往回搜尋到起點，同時將這一路上經過的路徑加一條edge
* findcircuit

   當新的edge都添加完畢後，便尋找如何經過所有edge的路線。先搜尋與該vertex相連的edges，與其中之一相連，刪去 `map`的對應位置，存進`edges`並遞迴搜尋，直到終點vertex沒有edge可以相連為止。經由比較行走距離是否和`node_name`中的edges數量相等，若不相等，則代表此路徑並非完整走過每條edge，因此將重新搜尋，直到相等

## 執行結果
* 輸入檔案topo.txt
   圖形表示：

![image](https://github.com/claireyy23/graph_theory/blob/master/%E6%8A%95%E5%BD%B1%E7%89%871.JPG)
* 輸出檔案
   * postman_path.txt
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/txt%E8%BC%B8%E5%87%BA.JPG)
   * path.dot轉成png檔 (視為無向)
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/%E6%8A%95%E5%BD%B1%E7%89%872.JPG)
      
* 終端機
   1. 計算vertex個數、搜尋每個vertex的degree、紀錄odd degree
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_vertex.JPG)
      
   2. 建立adjacent matrix `map` (a=1,b=2,c=3,...)
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_inimap.JPG)
      
   3. 將odd vertex依照最短路徑連edges
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_addpath.JPG)
      
   4. 更新 `map`
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_newmap.JPG)
      
   5. 輸出path
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_path.JPG)
      
   6. 清空後的 `map`
   
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_finalmap.JPG)
      
 * 輸入unconnected圖形
 
      ![image](https://github.com/claireyy23/graph_theory/blob/master/terminal_not%20connect.JPG)
      
      
      
