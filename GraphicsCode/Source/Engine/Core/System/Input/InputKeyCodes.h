#pragma once

namespace Input
{
    enum class Key : unsigned int
    {
        // From glfw3.h
        Space = 32,
        Apostrophe = 39, /* ' */
        Comma = 44, /* , */
        Minus = 45, /* - */
        Period = 46, /* . */
        ForwardSlash = 47, /* / */

        num0 = 48, /* 0 */
        num1 = 49, /* 1 */
        num2 = 50, /* 2 */ 
        num3 = 51, /* 3 */
        num4 = 52, /* 4 */
        num5 = 53, /* 5 */
        num6 = 54, /* 6 */
        num7 = 55, /* 7 */
        num8 = 56, /* 8 */
        num9 = 57, /* 9 */

        Semicolon = 59, /* ; */
        Equal = 61, /* = */

        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,

        LeftSqBracket = 91, /* [ */
        Backslash = 92, /* \ */
        RightSqBracket = 93, /* ] */
        Accent = 96, /* ` */

        /* Function keys */
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Delete = 261,


        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,



        /* NumPad Keys */
        Numpad0 = 320,
        Numpad1 = 321,
        Numpad2 = 322,
        Numpad3 = 323,
        Numpad4 = 324,
        Numpad5 = 325,
        Numpad6 = 326,
        Numpad7 = 327,
        Numpad8 = 328,
        Numpad9 = 329,
        NumpadPeriod = 330,
        NumpadDivide = 331,
        NumpadMultiply = 332,
        NumpadSubtract = 333,
        NumpadAdd = 334,
        NumpadEnter = 335,
        NumpadEqual = 336,

        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,

        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,

    };

    enum MouseButton
    {
        Left = 0,
        Middle = 1,
        Right = 2,
        NoCursor = 3,
    };
}
