//
3 // SFML - Simple and Fast Multimedia Library
4 // Copyright (C) 2007-2018 Laurent Gomila (laurent@sfml-dev.org)
5 //
6 // This software is provided 'as-is', without any express or implied warranty.
7 // In no event will the authors be held liable for any damages arising from the use of this software.
8 //
9 // Permission is granted to anyone to use this software for any purpose,
10 // including commercial applications, and to alter it and redistribute it freely,
11 // subject to the following restrictions:
12 //
13 // 1. The origin of this software must not be misrepresented;
14 //    you must not claim that you wrote the original software.
15 //    If you use this software in a product, an acknowledgment
16 //    in the product documentation would be appreciated but is not required.
17 //
18 // 2. Altered source versions must be plainly marked as such,
19 //    and must not be misrepresented as being the original software.
20 //
21 // 3. This notice may not be removed or altered from any source distribution.
22 //
24
25 #ifndef SFML_TRANSFORMABLE_HPP
26 #define SFML_TRANSFORMABLE_HPP
27
29 // Headers
31 #include <SFML/Graphics/Export.hpp>
32 #include <SFML/Graphics/Transform.hpp>
33
34
35 namespace sf
36 {
    41 class SFML_GRAPHICS_API Transformable
    42 {
        43 public:
        44
        49     Transformable();
        50
        55     virtual ~Transformable();
        56
        70     void setPosition(float x, float y);
        71
        84     void setPosition(const Vector2f& position);
        85
        98     void setRotation(float angle);
        99
        113     void setScale(float factorX, float factorY);
        114
        127     void setScale(const Vector2f& factors);
        128
        145     void setOrigin(float x, float y);
        146
        162     void setOrigin(const Vector2f& origin);
        163
        172     const Vector2f& getPosition() const;
        173
        184     float getRotation() const;
        185
        194     const Vector2f& getScale() const;
        195
        204     const Vector2f& getOrigin() const;
        205
        223     void move(float offsetX, float offsetY);
        224
        240     void move(const Vector2f& offset);
        241
        255     void rotate(float angle);
        256
        274     void scale(float factorX, float factorY);
        275
        292     void scale(const Vector2f& factor);
        293
        302     const Transform& getTransform() const;
        303
        312     const Transform& getInverseTransform() const;
        313
        314 private:
        315
        317     // Member data
        319     Vector2f          m_origin;
        320     Vector2f          m_position;
        321     float             m_rotation;
        322     Vector2f          m_scale;
        323     mutable Transform m_transform;
        324     mutable bool      m_transformNeedUpdate;
        325     mutable Transform m_inverseTransform;
        326     mutable bool      m_inverseTransformNeedUpdate;
        327 };
    328
    329 } // namespace sf
330
331
332 #endif // SFML_TRANSFORMABLE_HPP
333
334
