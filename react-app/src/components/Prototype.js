import React, { useEffect } from 'react';
import styled from 'styled-components';

import { BACKGROUND_COLOR, WIDTH, HEIGHT } from 'const';
import * as animations from 'animations';
import { useCanvas } from 'hooks';
import { LEVELS } from 'models/Level';
import { getStrDiscRadii, getStrDiscAngles, getStrMaxRadius } from 'utils';

const Container = styled.div`
  background-color: ${BACKGROUND_COLOR};
  height: 100%;
  text-align: center;
  border: 1px solid #000;
`;

console.log(
  'LEDs per level:\n',
  LEVELS.map(level => level.allLeds.length)
);
console.log(
  'Total LED count:',
  LEVELS.reduce((acc, level) => acc + level.allLeds.length, 0)
);
console.log('LEVELS', LEVELS);
console.log(getStrDiscRadii(LEVELS));
console.log(getStrMaxRadius(LEVELS));
console.log(getStrDiscAngles(LEVELS));

const Prototype = () => {
  const [canvasRef, context] = useCanvas();

  useEffect(() => {
    if (window.reqId) {
      window.cancelAnimationFrame(window.reqId);
    }
    if (context) {
      animations.lines(context, LEVELS);

      //animations.showLEDs(context, LEVELS);

      // Output each angle value as text to verify they are correct
      //context.fillStyle = 'white';
      //LEVELS.forEach(level =>
      //  level.allLeds.forEach((led, i) => {
      //    context.fillText(level.angles[i], led.x, led.y);
      //  })
      //);
    }
  }, [context]);

  return (
    <Container>
      <canvas ref={canvasRef} width={WIDTH} height={HEIGHT} />
    </Container>
  );
};

export default Prototype;
