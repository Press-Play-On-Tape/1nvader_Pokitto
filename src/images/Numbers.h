#pragma once

namespace Images {

    namespace Portrait {

        namespace Normal {

            #include "numbers/portrait/normal/Number_0.h"
            #include "numbers/portrait/normal/Number_1.h"
            #include "numbers/portrait/normal/Number_2.h"
            #include "numbers/portrait/normal/Number_3.h"
            #include "numbers/portrait/normal/Number_4.h"
            #include "numbers/portrait/normal/Number_5.h"
            #include "numbers/portrait/normal/Number_6.h"
            #include "numbers/portrait/normal/Number_7.h"
            #include "numbers/portrait/normal/Number_8.h"
            #include "numbers/portrait/normal/Number_9.h"

            const uint8_t * const Numbers[] = { 
                Number_0,
                Number_1,
                Number_2,
                Number_3,
                Number_4,
                Number_5,
                Number_6,
                Number_7,
                Number_8,
                Number_9,
            };

        };

        namespace Rotated {

            #include "numbers/portrait/rotated/Number_0.h"
            #include "numbers/portrait/rotated/Number_1.h"
            #include "numbers/portrait/rotated/Number_2.h"
            #include "numbers/portrait/rotated/Number_3.h"
            #include "numbers/portrait/rotated/Number_4.h"
            #include "numbers/portrait/rotated/Number_5.h"
            #include "numbers/portrait/rotated/Number_6.h"
            #include "numbers/portrait/rotated/Number_7.h"
            #include "numbers/portrait/rotated/Number_8.h"
            #include "numbers/portrait/rotated/Number_9.h"

            const uint8_t * const Numbers[] = {
                //Number_0,
                Number_1,
                //Number_2,
                Number_3,
                Number_4,
                //Number_5,
                Number_6,
                Number_7,
                //Number_8,
                Number_9,
            };

        };

    };

    namespace Landscape {

        #include "numbers/landscape/Number_0.h"
        #include "numbers/landscape/Number_1.h"
        #include "numbers/landscape/Number_2.h"
        #include "numbers/landscape/Number_3.h"
        #include "numbers/landscape/Number_4.h"
        #include "numbers/landscape/Number_5.h"
        #include "numbers/landscape/Number_6.h"
        #include "numbers/landscape/Number_7.h"
        #include "numbers/landscape/Number_8.h"
        #include "numbers/landscape/Number_9.h"

        const uint8_t * const Numbers[] = { 
            Number_0,
            Number_1,
            Number_2,
            Number_3,
            Number_4,
            Number_5,
            Number_6,
            Number_7,
            Number_8,
            Number_9,
        };

    };

};
