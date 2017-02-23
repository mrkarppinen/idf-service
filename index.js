
var solitaire = require('./build/Release/solitaire'),
    mount = require('koa-mount'),
    koa = require('koa'),
    bodyParser = require('koa-bodyparser'),
    cors = require('koa-cors');



function solveSolitaire(solve){
  return new Promise ((resolve, reject) => {
    solitaire.search(solve, (response) => { resolve(response); });
  });
}

var app = koa();


app.use(cors({origin: true}));
app.use(bodyParser());

app.use(mount('/solitaire', function *(){

  yield solveSolitaire(this.request.body.s).then((response) => {
    let arr = response.split(';');

    this.status = 200;
    this.body = {result: arr};
  });

}));


app.listen(3200);
console.log('listening on port 3200');
