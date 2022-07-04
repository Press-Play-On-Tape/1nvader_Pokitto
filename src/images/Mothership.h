#pragma once

namespace Images {

    namespace Portrait {
            
        namespace Normal {

            #include "mothership/portrait/normal/MotherShip_00.h"
            #include "mothership/portrait/normal/MotherShip_01.h"
            #include "mothership/portrait/normal/MotherShip_02.h"
            #include "mothership/portrait/normal/MotherShip_03.h"

            const uint8_t * const Mothership[] = { 
                MotherShip_00,
                MotherShip_01,
                MotherShip_02,
                MotherShip_03,
            };

        }

        namespace Rotated {

            #include "mothership/portrait/rotated/MotherShip_00.h"
            #include "mothership/portrait/rotated/MotherShip_01.h"
            #include "mothership/portrait/rotated/MotherShip_02.h"
            #include "mothership/portrait/rotated/MotherShip_03.h"

            const uint8_t * const Mothership[] = { 
                MotherShip_00,
                MotherShip_01,
                MotherShip_02,
                MotherShip_03,
            };

        }

        namespace SIZE_3X3 {

            #include "mothership/portrait/3x3/MotherShip_Title_00.h"
            #include "mothership/portrait/3x3/MotherShip_Title_01.h"
            #include "mothership/portrait/3x3/MotherShip_Title_02.h"
            #include "mothership/portrait/3x3/MotherShip_Title_03.h"

            const uint8_t * const Mothership_Title[] = { 
                MotherShip_Title_00,
                MotherShip_Title_01,
                MotherShip_Title_02,
                MotherShip_Title_03,
            };

        }

        namespace SIZE_2X2 {

            #include "mothership/portrait/2x2/MotherShip_Title_00.h"
            #include "mothership/portrait/2x2/MotherShip_Title_01.h"
            #include "mothership/portrait/2x2/MotherShip_Title_02.h"
            #include "mothership/portrait/2x2/MotherShip_Title_03.h"

            const uint8_t * const Mothership_Title[] = { 
                MotherShip_Title_00,
                MotherShip_Title_01,
                MotherShip_Title_02,
                MotherShip_Title_03,
            };

        }

        #include "mothership/portrait/Bomb.h"

    }

    namespace Landscape {

        #include "mothership/landscape/MotherShip_00.h"
        #include "mothership/landscape/MotherShip_01.h"
        #include "mothership/landscape/MotherShip_02.h"
        #include "mothership/landscape/MotherShip_03.h"

        const uint8_t * const Mothership[] = { 
            MotherShip_00,
            MotherShip_01,
            MotherShip_02,
            MotherShip_03,
        };

        namespace SIZE_3X3 {

            #include "mothership/landscape/3x3/MotherShip_Title_00.h"
            #include "mothership/landscape/3x3/MotherShip_Title_01.h"
            #include "mothership/landscape/3x3/MotherShip_Title_02.h"
            #include "mothership/landscape/3x3/MotherShip_Title_03.h"

            const uint8_t * const Mothership_Title[] = { 
                MotherShip_Title_00,
                MotherShip_Title_01,
                MotherShip_Title_02,
                MotherShip_Title_03,
            };

        }

        namespace SIZE_2X2 {

            #include "mothership/landscape/2x2/MotherShip_Title_00.h"
            #include "mothership/landscape/2x2/MotherShip_Title_01.h"
            #include "mothership/landscape/2x2/MotherShip_Title_02.h"
            #include "mothership/landscape/2x2/MotherShip_Title_03.h"

            const uint8_t * const Mothership_Title[] = { 
                MotherShip_Title_00,
                MotherShip_Title_01,
                MotherShip_Title_02,
                MotherShip_Title_03,
            };

        }

        #include "mothership/landscape/Bomb.h"

    }

};
