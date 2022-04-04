import React, { useEffect, useState } from 'react';
import styled from 'styled-components';

import { BACKGROUND_COLOR, WIDTH, HEIGHT } from 'const';
import * as animations from 'animations';
import { useCanvas } from 'hooks';
import { DISCS_PETALS as DISCS } from 'models/Discs';

const Container = styled.div`
  background-color: ${BACKGROUND_COLOR};
  height: 100%;
  text-align: center;
`;

console.log(
  'Total LED count:',
  DISCS.reduce((acc, disc) => acc + disc.leds.flatMap(x => x).length, 0)
);
console.log('DISCS', DISCS);
console.log(
  DISCS.map((disc, i) => `int16_t radiusDisc${i}[] = \{${disc.radii.join(', ')}\};`).join('\n')
);

const animationList = ['Ripple', 'Juggle', 'Stop'];

const Prototype = () => {
  const [canvasRef, context] = useCanvas();
  const [animation, setAnimation] = useState(0);

  useEffect(() => {
    if (window.reqId) {
      window.cancelAnimationFrame(window.reqId);
    }
    if (context) {
      animations.showLEDs(context, DISCS);
      switch (animation) {
        case 'Ripple':
          //animations.ripple(context, DISCS);
          //animations.petalRipple(context, DISCS);
          animations.radiusRipple(context, DISCS);
          break;
        case 'Juggle':
          animations.juggle(context, DISCS);
          break;
        default:
          break;
      }
    }
  }, [animation, context]);

  return (
    <Container>
      {animationList.map((animation, i) => (
        <button key={i} onClick={() => setAnimation(animation)}>
          {animation}
        </button>
      ))}
      <canvas ref={canvasRef} width={WIDTH} height={HEIGHT} />
    </Container>
  );
};

export default Prototype;
