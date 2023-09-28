#version 450
out vec4 FragColor;
in vec2 UV;
uniform vec3 iResolution;
uniform float iTime;
uniform float iTimeDelta;
uniform float iFrameRate;
uniform int iFrame;
uniform float iChannelTime[4];
uniform vec3 iChannelResolution[4];
uniform vec4 iMouse;
uniform samplerXX;

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    
    vec2 uv = fragCoord/iResolution.xy;

    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));

    vec2 sunUV = uv * 2.0 - 1.0;
    sunUV.x *= iResolution.x / iResolution.y;
    float d = distance(sunUV,vec2(0.0,sin(iTime)));
    d = smoothstep(0.5,0.6,d);
    col = mix(vec3(1.0,1.0,0.0),col,d);

    float y = sin(uv.x*4.0)*0.5+0.1;
    float t = step(y,uv.y);
    col = mix(vec3(0.0,0.4,0.0),col,t);

    //vec3 color = mix(vec3(1.0,1.0,0.0),vec3(0.9,0.0,0.5),uv.y);

    //float hills = 1.0 - step(sin(uv.x*6.0) * 0.2 + 0.3,uv.y);

    //color = mix(color,vec3(0.2),hills);

    fragColor = vec4(col,1.0);
}