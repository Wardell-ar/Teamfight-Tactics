//导入http
const http = require('http');
//创建web
const server = http.createServer();
//绑定
server.on('request',function(req,res){
  console.log('Someone visit our web server.')
})
//启动服务器
server.listen(80,function(){
    console.log('server running at http://127.0.0.1')
})