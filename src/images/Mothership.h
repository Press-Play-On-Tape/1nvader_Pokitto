#pragma once

#include "../utils/Enums.h"

namespace Images {

    namespace Portrait {
            
        namespace Normal {

            #ifdef NEW_GRAPHICS

                #include "mothership/portrait/normal/MotherShip_04.h"
                #include "mothership/portrait/normal/MotherShip_05.h"

                #include "mothership/portrait/normal/MotherShip_04_Red.h"
                #include "mothership/portrait/normal/MotherShip_05_Red.h"

                const uint8_t * const Mothership[] = { 
                    MotherShip_04,
                    MotherShip_05,
                    MotherShip_04_Red,
                    MotherShip_05_Red,
                };

            #else

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

            #endif

        }

        namespace Rotated {

            #ifdef NEW_GRAPHICS
                
                #include "mothership/portrait/rotated/MotherShip_04.h"
                #include "mothership/portrait/rotated/MotherShip_05.h"
                
                #include "mothership/portrait/rotated/MotherShip_04_Red.h"
                #include "mothership/portrait/rotated/MotherShip_05_Red.h"

                const uint8_t * const Mothership[] = { 
                    MotherShip_04,
                    MotherShip_05,
                    MotherShip_04_Red,
                    MotherShip_05_Red,
                };

            #else
                
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

            #endif

        }

        namespace SIZE_3X3 {

            #ifdef NEW_GRAPHICS
                
                #include "mothership/portrait/3x3/MotherShip_Title_04.h"
                #include "mothership/portrait/3x3/MotherShip_Title_05.h"

                const uint8_t * const Mothership_Title[] = { 
                    MotherShip_Title_04,
                    MotherShip_Title_05,
                };

            #else
                
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

            #endif

        }

        namespace SIZE_2X2 {

            #ifdef NEW_GRAPHICS
                
                #include "mothership/portrait/2x2/MotherShip_Title_04.h"
                #include "mothership/portrait/2x2/MotherShip_Title_05.h"

                const uint8_t * const Mothership_Title[] = { 
                    MotherShip_Title_04,
                    MotherShip_Title_05,
                };

            #else
                
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

            #endif

        }

        #include "mothership/portrait/Bomb.h"

    }

    namespace Landscape {

        #ifdef NEW_GRAPHICS
        
            #include "mothership/landscape/MotherShip_04.h"
            #include "mothership/landscape/MotherShip_05.h"
        
            #include "mothership/landscape/MotherShip_04_Red.h"
            #include "mothership/landscape/MotherShip_05_Red.h"

            const uint8_t * const Mothership[] = { 
                MotherShip_04,
                MotherShip_05,
                MotherShip_04_Red,
                MotherShip_05_Red,
            };

        #else

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

        #endif

        namespace SIZE_3X3 {

            #ifdef NEW_GRAPHICS
    
                #include "mothership/landscape/3x3/MotherShip_Title_04.h"
                #include "mothership/landscape/3x3/MotherShip_Title_05.h"

                const uint8_t * const Mothership_Title[] = { 
                    MotherShip_Title_04,
                    MotherShip_Title_05,
                };

            #else
    
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

            #endif

        }

        namespace SIZE_2X2 {

            #ifdef NEW_GRAPHICS

                #include "mothership/landscape/2x2/MotherShip_Title_04.h"
                #include "mothership/landscape/2x2/MotherShip_Title_05.h"

                const uint8_t * const Mothership_Title[] = { 
                    MotherShip_Title_04,
                    MotherShip_Title_05,
                };

            #else

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

            #endif

        }

        #include "mothership/landscape/Bomb.h"

    }

};
