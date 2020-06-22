				

# tcp/udp (socket en in c)

###* tcp client/server
###* udp client/server

Ce projet est effectué dans le cadre d'un TP de la cour de réseau de L3INFO de la faculté de science à l'université paris Saclay
Il s'agissait de créer une connexion client/server en mode udp et une autre en mode tcp grâce aux sockets
 Veillez trouver l'énoncée sur le lien github : [ https://www.github.com/2chenj/reseau/sockets ]

## Obtenir le code : 
Les connexions ont été implémenté en c donc vous devez avoir des outils du langage de programmation c pour tester les connexions 
Pour se procurer les fichiers, télécharger ou cloner le repository avec cette ligne de commande Git clone lien github
Depuis un terminal,compiler les quatre fichier un par un

> gcc udp_server.c -o udp_server
> gcc tcp_server.c -o tcp_server
> gcc udp_client.c -o udp_client
> gcc tcp_client.c -o tcp_client

#### Il faut toujours exécuter le serveur avant le client 
Pour le mode tcp par exemple ouvrer deux terminaux
Dans le premier terminal faites
> ./tcp_server anyPortNmberForTheSever

Puis dans le second terminal faites
> ./tcp_client anyIpAddForThisClient aPortNumberSameAsTheServers

Voilà une connexion client/serveur en mode tcp est établi entre le terminal exécutant le client
Et celui exécutant le serveur, vous parler au serveur depuis le terminal du client

## Principales fonctionnalités 
Le socket permet un client de se connecter au server avec la fonction sendTo si ce client possède des infos sur l'adresse IP
Du serveur et le port sur lequel le serveur écoute 
Dans le mode tcp on se connect au serveur grâce à fonction connect cela a beaucoup d'avantage notamment
On a plus besoin de spécifier l’IP et le port systématiquement à l’appel des fonction send et receive
Dans cet implémentation (tcp) nous mettrons en place un serveur qui peux accueillir plusieurs clients, le nombre maximal de client est spécifier dans la fonction accepte du serveur
Pour accepter plusieurs clients on a mis une boucle while qui accepte les clients qui se connecte au serveur
Puis lorsqu'un client se connecte au serveur un cree un processus propre à ce client grâce à la fonction fork() en c ainsi tous le clients peuvent  communiquer avec le serveur "simultanément". 

pour le moment je n'ai pas reussi à faire en sorte à ce que tous le clients voyent les messages des un des autres !

Aussi j'aurais anormement aimé pouvoir mettre le fichier server.c sur le serveur de la fac et de pouvoir se connecter dessus depuis
chez moi mais malheureusement je n'ai pas reussi ! j'ai pourtant reussi à récuperer l'adresse IP du serveur voire ci-dessus !


//**********************client socket and server
    
  ************************ disant server ****************************** 
    const char* hostName ="tp-ssh1.dep-informatique.u-psud.fr"; 
    struct addrinfo paramToFollow;
    struct addrinfo *resultats;
    struct addrinfo *addrIter;
    struct sockaddr_in *ip_acces;
        //hints
    memset(&paramToFollow,0,sizeof paramToFollow);
    paramToFollow.ai_family = PF_INET;
    paramToFollow.ai_socktype = SOCK_DGRAM;
    
    int rv;
           //checkp host name
    if( (rv=getaddrinfo(hostName,"9600",&paramToFollow,&resultats)) != 0 ){
	    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
	    return 1;
    }
    ip_acces = (struct sockaddr_in *) resultats->ai_addr;
    printf("IP adress without for is : %s\n",inet_ntoa(ip_acces->sin_addr));

    struct sockaddr_in serverSocketInfo;
    serverSocketInfo.sin_family = ip_acces->sin_family;
    serverSocketInfo.sin_addr = ip_acces->sin_addr;
    serverSocketInfo.sin_port = ip_acces->sin_port;

    struct in_addr serverAddr;
    serverAddr = ip_acces->sin_addr;

    //******************** end distant server

## Auteurs :
Ce projet a été réalisé par habinshuti thierry alias 2chenj@github
License : 
Cette implémentation est une open source et libre de droit !
