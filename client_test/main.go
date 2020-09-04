package main


import (
	"net"
	"log"
	"os"
)


func main() {
	
	ip := "127.0.0.1";
	port := "8085";

	gsAddr := ip + ":" + port;
	tcpAddr, err := net.ResolveTCPAddr("tcp4", gsAddr)

	checkErr(err)

	conn, err := net.DialTCP("tcp", nil, tcpAddr)

	log.Println("connect");

	checkErr(err)

	sendData := "whoami"

	conn.Write([]byte(sendData))

	log.Println("write msg");
}

func checkErr(err error) {
	if err != nil {
			log.Println(err.Error())
			os.Exit(1)
	}
}


