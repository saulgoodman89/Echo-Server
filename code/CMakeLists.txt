#PROJECT() 프로젝트 이름 설정 
PROJECT(Echo-Server) 

#CMAKE_PROJECT_NAME 프로젝트 이름 변수. PROJECT() 이름이 이 변수에 저장된다.  

#[[ 
	CMAKE_MINIMUM_REQUIRED : 필요 CMake 최소 버전 명시 
	CMAKE_MINIMUM_REQUIRED (VERSION <버전>)
    	CMAKE_MINIMUM_REQUIRED (VERSION 2.8) 

]]
CMAKE_MINIMUM_REQUIRED (VERSION 3.16)

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

SET(CMAKE_THREAD_PREFER_PTHREAD TRUE)
SET(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

SET ( SERVER_SRC_FILES server.c)
ADD_EXECUTABLE(Server ${SERVER_SRC_FILES})
ADD_EXECUTABLE(Client client.c)

target_link_libraries(Server Threads::Threads)


#[[ MESSAGE ( [<Type>] <메시지> )
Type은 생략 가능하며 Type 생략 시 메시지를 출력.

STATUS , WARNING , AUTHOR_WARNING , SEND_ERROR , FATAL_ERROR 총 5개의 종류가 있다. 
STATUS : 상태 메시지 출력. 메시지 앞에 '--'가 추가 출력
WARNING : 경고 메시지를 출력하고 계속 진행. 
AUTHOR_WARNING : 프로젝트 개발자용 경고 메시지를 출력하고 계속 진행. 
SEND_ERROR : 오류 메시지를 출력하고 계속 진행하지만 , Makefile 생성은 하지 않음. 
FATAL_ERROR : 오류 메시지를 출력하고 작업을 즉시 중단

MESSAGE (" DEFAULT ")
MESSAGE( STATUS " MESSAGE STATUS ")
MESSAGE( WARNING " MESSAGE WARNING ")
MESSAGE( AUTHOR_WARNING " MESSAGE AUTHOR WARNING " )
MESSAGE( SEND_ERROR " MESSAGE SEND_ERROR " )
MESSAGE( FATAL_ERROR " MESSAGE FATAL_ERROR ")

 DEFAULT 
--  MESSAGE STATUS 
CMake Warning at CMakeLists.txt:53 (MESSAGE):
   MESSAGE WARNING 


CMake Warning (dev) at CMakeLists.txt:54 (MESSAGE):
   MESSAGE AUTHOR WARNING 
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Error at CMakeLists.txt:55 (MESSAGE):
   MESSAGE SEND_ERROR 


CMake Error at CMakeLists.txt:56 (MESSAGE):
   MESSAGE FATAL_ERROR 



]]

#[[
	MAKE_VERBOSE_MAKEFILE false
		[ 25%] Building C object CMakeFiles/Client.dir/client.c.o
		[ 50%] Linking C executable Client
		[ 50%] Built target Client
		[ 75%] Building C object CMakeFiles/Server.dir/server.c.o
		[100%] Linking C executable Server
		[100%] Built target Server

	MAKE_VERBOSE_MAKEFILE ture
		-- Configuring done
		-- Generating done
		-- Build files have been written to: /home/keg/dev/Echo-Server/code
		[ 25%] Building C object CMakeFiles/Client.dir/client.c.o
		[ 50%] Linking C executable Client
		[ 50%] Built target Client
		[ 75%] Building C object CMakeFiles/Server.dir/server.c.o
		[100%] Linking C executable Server
		[100%] Built target Server


]]
SET ( MAKE_VERBOSE_MAKEFILE true )


#[[ 
	ADD_LIBRARY
	ADD_LIBRARY ( <라이브러리_이름> [STATIC|SHARED|MODULE] <소스_파일> <소스_파일> ... )
	-- Configuring done
	-- Generating done
	-- Build files have been written to: /home/keg/dev/Echo-Server/code
	Scanning dependencies of target echo
	[ 14%] Building C object CMakeFiles/echo.dir/server.c.o
	[ 28%] Building C object CMakeFiles/echo.dir/client.c.o
	[ 42%] Linking C static library libecho.a
	[ 42%] Built target echo
	[ 71%] Built target Client
	[100%] Built target Server


]]
ADD_LIBRARY( echo STATIC server.c client.c)


ADD_CUSTOM_TARGET( server 
COMMENT "build server"
WORKING_DIRECTORY ${SRC}
COMMAND gcc -o Server server.c -lpthread )

ADD_DEPENDENCIES(server Server)

SET ( CMAKE_INSTALL_PREFIX ./) 

INSTALL( TARGETS Server 
RUNTIME DESTINATION ./bin  
ARCHIVE DESTINATION ./lib
LIBRARY DESTINATION ./lib )

SET ( CMAKE_EXE_LINKER_FLAGS_DEBUG "-DCONFIG_DEBUG -Wl, -whole-archive" )
SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/output )
SET ( CMAKE_LIBRARY_OUTPUT_DIRECTORY lib/ )


SET ( PROJECT_VERSION_MAJOR 2 )
SET ( PROJECT_VERSION_MINOR 0 )
SET ( PROJECT_VERSION_PATCH 2 )
SET ( PROJECT_VERSION_TWEAK 3 )

CONFIGURE_FILE ( echoTemp.h.in version.h ) 
#TARGET_COMPILE_DEFINITIONS( server PUBLIC -PORT=99 )


ADD_CUSTOM_COMMAND (
	                OUTPUT Server
					                COMMENT "Generating binary from executable"
									                DEPENDS server.c
													                COMMAND gcc -o Server server.c -lpthread
																	)
