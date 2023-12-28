#version 420 core

float resX = 1920;
float resY = 1080;

out vec4 o_frag_color;

void main()
{
	vec2 uv = vec2(gl_FragCoord.x / resX, gl_FragCoord.y / resY);    
    float atmosphere = sqrt(1.0-uv.y);
    vec3 skyColor = vec3(0.2,0.4,0.8);    
    float scatter = pow(0.2, 1.0 / 15.0);
    scatter = 1.0 - clamp(scatter,0.8,1.0);    
    vec3 scatterColor = mix(vec3(1.0),vec3(1.0,0.3,0.0) * 1.5,scatter);        
	o_frag_color = vec4(mix(skyColor, vec3(scatterColor), atmosphere / 1.3), 1.0);

}