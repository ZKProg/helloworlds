import http, { Server } from 'http'
import dgram from 'dgram'
import { Buffer } from 'buffer'
import { parse } from 'path'
import url from 'url'

var rpos = {}
const xquery = 'RPOS\x001\x00'
const xquerybytes = Buffer.from(xquery)


// Server Http.......................................................

var server = http.createServer((req, res) => {
  let path = url.parse(req.url).pathname;

  if (path = '/rpos')
  {
    res.writeHead(200, {'Content-Type': 'application/json'})
    res.write(JSON.stringify(rpos))
    res.end()
  }
})

// Socket.............................................................


const client = dgram.createSocket('udp4')
client.bind(49011, '127.0.0.1')

client.send(xquerybytes, 49000, '127.0.0.1', (err) => {
  if (err)
  {
    console.log('Error: %s', err.message)
    client.close()
  }
  else
  {
    console.log('Data send to server')
  }
  
})

client.on('message', (msg, rinfo) => {
  //console.log('message received!')
  let header = msg.subarray(0, 4).toString()
  let data = msg.subarray(5, Buffer.byteLength(msg))
  
  try {
    let lon = data.readDoubleLE(0);
    let lat = data.readDoubleLE(8);
    let alt = data.readDoubleLE(16);
    let height = data.readFloatLE(24);
    
    rpos = {
      'lon': lon,
      'lat': lat,
      'alt': alt * 3.28084,
      'height': height * 3.28084
    }

    console.log(rpos)
  }
  catch (e) {
    if (e instanceof RangeError && e.code === 'ERR_BUFFER_OUT_OF_BOUNDS') {
      console.log(e.message)
    }

  }
  console.log('-----------------------------')
})


// Main.......................................................................
server.listen(2609)