const express = require('express');
const { createCanvas } = require('canvas');
const app = express();
app.use(express.json());

app.use((req, res, next) => {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

app.get('/test', async (req, res, next) => {
  res.setHeader('content-type', 'application/octet-stream');
  res.end(prepareCanvas());
})

app.listen(3000, () => console.log('web server listening on port 3000'));

const prepareCanvas = () => {
  const canvas = createCanvas(488, 600);
  const ct = canvas.getContext('2d');

  ct.clearRect(0, 0, 488, 600);
  ct.fillStyle = 'rgb(255, 255, 250)';
  ct.fillRect(0, 0, 488, 600);
  ct.fillStyle = 'black';

  ct.moveTo(0, 0);
  ct.fillText("SUPER TEST!", 10, 10);

  return canvasToText(ct);
}

const canvasToText = (ct) => {
  const imgData = ct.getImageData(0, 0, 488, 600).data;
  const img2txt = imgData.reduce((prev, curr, i) => toMonochrome(prev, curr, i, imgData), []);
  const lastDataPos = img2txt.lastIndexOf(1);
  img2txt.length = lastDataPos + 1;

  return img2txt.join('') + '2';
}

const toMonochrome = (prev, curr, i, imgData) => {
  const threshold = 118;

  if (i % 4 === 0) {
    const luma = imgData[i] * 0.3 + imgData[i + 1] * 0.59 + imgData[i + 2] * 0.11;
    prev.push(luma < threshold ? 1 : 0);
  }

  return prev;
}
