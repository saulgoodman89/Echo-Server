# Echo-Server

Echo Server란 ?
클라이언트가 전송해주는 데이터를 그대로 되돌려 전송해주는 기능을 가진 서버 
- 클라이언트가 서버로부터 몇 바이트의 데이터를 수신할 것인지 예상 할 수 있다. 

## 관련 지식


## Build

### 전체빌드
```
make all

```

### 전체 실행 파일 , 오브젝트 파일 제거 
```

make clean

```

### 서버 / 클라이언트만 빌드
```
make server or make client

```
### 서버만 실행파일 , 오브젝트 파일 제거 
```
make clean_server or make clean_client

```
