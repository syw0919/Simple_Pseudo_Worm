# Simple_Pseudo_Worm

## Information

본 프로그램은 국립공주대학교정보보호영재교육원 프로젝트 발표 용도로 제작된

이른 바 "유사 웜바이러스"입니다.

### Warning

가상환경 이외에서는 컴파일 및 실행을 권장하지 않습니다.

### 추후 수정사항

FileSearch() 함수의 동작 방식이 지저분하므로

전역변수를 활용하여 C:\ 부터 탐색을 시작해

자기복제를 할 수 있도록 만들 계획입니다.

탐색에 멀티스레딩을 활용하여 컴퓨터의 자원을 더욱 소모시킬 수 있을 것입니다.

정리하자면

1. FileSearch() 함수의 동작 방식 개선
2. 탐색에 멀티스레딩 활용