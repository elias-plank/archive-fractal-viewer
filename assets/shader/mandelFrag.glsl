#version 450
layout (location = 0) out vec4 outColor;

// uniforms
uniform int depth;
uniform double screenRatio;
uniform dvec2 screenSize;
uniform dvec2 center;
uniform double zoom;
uniform int theme;

vec4 orangeTheme(float t);
vec4 blueTheme(float t);

void main()
{
    dvec2 z, c;
    c.x = screenRatio * (gl_FragCoord.x / screenSize.x - 0.5);
    c.y = (gl_FragCoord.y / screenSize.y - 0.5);

    c.x /= zoom;
    c.y /= zoom;

    c.x += center.x;
    c.y += center.y;

    int i;
    for (i = 0; i < depth; i++) {
        double x = (z.x * z.x - z.y * z.y) + c.x;
		double y = (z.y * z.x + z.x * z.y) + c.y;

		if((x * x + y * y) > 2.0) break;
		z.x = x;
		z.y = y;
    }
    
    if (theme == 0) {
    
        outColor = blueTheme(float(i) / float(depth));
    }
    else if(theme == 1) {
    
        outColor = orangeTheme(float(i));
    }
    else {
    
        outColor = vec4(0.0f);
    }
}

vec4 blueTheme(float t) {
    
    float r = 9.0 * (1.0 - t) * t * t * t;
    float g = 15.0 * (1.0 - t) * (1.0 - t) * t * t;
    float b = 8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t;

    return vec4(r, g, b, 1.0);
}

vec4 orangeTheme(float t) {

    if(t < depth) {

        float a = log2(t * depth) * (t / float(depth));
        return vec4(0.5f * sin(a) + 0.5f, 0.5f * sin(a + 2.094f) + 0.5f, 0.5f * sin(a + 4.188f) + 0.5f, 1.0f);
    }
    else {
    
        return vec4(0.0f);
    }
}