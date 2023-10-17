# Audio File Converter

### 簡介
編曲軟體遇到不支援的檔案類型時，時常會需要上網進行轉檔，這是非常麻煩的，因此針對這個問題設計了VST Plugin，可以根據需求轉換音檔類型(比如 m4a -> mp3)，讓使用者可以在不離開編曲軟體的情況下，直接透過此plugin進行轉檔，進而節省轉檔所帶來的額外工作量。

## 使用方法
1. 將 vst3 放入 DAW 可以讀取的資料夾後，啟動 DAW 並開啟 Audio Converter。

2. 首次開啟時，需要先設定檔案輸出的資料夾(點擊 set output folder)。之後，程式會預設使用最後一次設定的資料夾。

3. 點擊 Upload 選擇欲轉換成mp4的音訊檔案。

4. 點擊 Convert，若出現 Success代表轉檔成功，可以到輸出的資料夾查看成果。若出現 Error，則需檢查輸入檔案類型是否有誤。


## 可優化項目
* 選擇轉檔類型，不局限於m4a轉mp4。
* 添加保護機制，避免錯誤的輸入型態。

## Bug Report
* cannot find ffmpeg reason: Open File, Open Folder會讓current folder變成打開的位置
* 改輸出檔名的方法要處理，才能用到m4a以外的檔案。
