#PROJECT() 프로젝트 이름 설정 
PROJECT(Echo-Server) 

#CMAKE_PROJECT_NAME 프로젝트 이름 변수. PROJECT() 이름이 이 변수에 저장된다.  

#[[
	콘솔에 메시지나 변수를 출력.
	빌드 스크립트 디버깅 시 요긴하게 사용.
	
	MESSAGE ( [<Type>] <메시지> )
]]
MESSAGE( ${CMAKE_PROJECT_NAME} )

#[[
	CMAKE_BUILD_TYPE : 빌드 Configuration
	빌드의 목적이 디비깅 혹은 릴리즈 인지에 따라 서로 다른 옵션을 지정하여 빌드
	
	Debug : 디버깅 목적의 빌드
	Release : 배포 목적의 빌드
	RelWithDebInfo : 배포 목적의 빌드지만 , 디버깅 정보 포함
	MinSizeRel : 최소 크기로 최적화한 배포 목적 빌드. 

	CMAKE_BUILD_TYPE을 지정하면 , Makefile 작성 시 빌드 type에 따라 서로 다른 빌드 옵션을 삽입해준다. 
	빌드 목적별로 빌드 스크립트를 따로 만들어주는것을 권장 
]]

#CMAKE_BUILD_TYPE


#[[
	SET(<변수명> <값>)
    	
    	변수참조는 $변수명 
	${<변수명>}  으로 한다. 
]]

SET ( SERVER_SRC_FILES server.c)
ADD_EXECUTABLE(Server ${SERVER_SRC_FILES})
ADD_EXECUTABLE(Client client.c)


#[[ 
	CMAKE_MINIMUM_REQUIRED : 필요 CMake 최소 버전 명시 
	CMAKE_MINIMUM_REQUIRED (VERSION <버전>)
    	CMAKE_MINIMUM_REQUIRED (VERSION 2.8) 

]]

