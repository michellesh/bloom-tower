import * as d3 from 'd3';

import { clearCanvas } from 'utils';
import { showLEDs } from 'animations';

export const lines = (context, levels) => {
  clearCanvas(context);

  let offsets = d3.range(levels.length).map(x => 0);
  const segmentLength = 10;

  const _lines = () => {
    levels.forEach((level, d) => {
      for (let i = 0; i < level.allLeds.length; i++) {
        if ((i + offsets[d]) % segmentLength === 0) {
          level.allLeds[i] = level.allLeds[i].on();
        } else {
          level.allLeds[i] = level.allLeds[i].off();
        }
      }
      offsets[d]++;
      if (offsets[d] > level.length) {
        offsets[d] = 0;
      }
    });

    showLEDs(context, levels);
    window.reqId = window.requestAnimationFrame(_lines);
  };

  window.reqId = window.requestAnimationFrame(_lines);
};
