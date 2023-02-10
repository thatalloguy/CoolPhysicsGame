#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec2 fragTexCoord;
//in vec4 fragColor;
in vec3 fragNormal;
in vec3 fPosition;
// Input uniform values
uniform sampler2D texture0;
uniform float time;
// Output fragment color
out vec4 finalColor;



#define PI 3.14159265359

float random(float pos, float range, float start)
{
   return start + mod(sin(pos*3.43)*23432.4, range);   
}

vec2 random(vec2 pos, vec2 range, vec2 start)
{
    float newX = sin(dot(pos, vec2(32.1232, 7.324)))*23432.4;
    float newY = cos(dot(pos, vec2(432.23, 21.4)))*32145.4;
    
    newX = start.x + mod(newX, range.x);
    newY = start.y + mod(newY, range.y);
    
    return vec2(newX, newY);
}

float floatRandom(vec2 pos, float range, float start)
{
    float val = cos(dot(pos, vec2(54.54, 6.766)))*12344.4;
	val = start + mod(val, range);
    return val;
}

void main()
{
    vec2 uv = fPosition.xy;
	vec3 col = vec3(0);
    vec3 waterCol = vec3(0, 0.5, 1.0);
    
    float minDist = 100.0;
    float minDist2 = 100.0;
    float d;
    float scale = 2.0;
    
    float speed = 2.5;
    vec2 newUv = scale*uv;
    float z = 1.0+(0.5 + 0.5*sin(newUv.y/2.0 + speed*time)/5.0);
    
	newUv /= z;
    
    vec2 frac = mod(newUv+vec2(0.5, 0.5), 1.0);
   	vec2 id = floor(newUv);
    
    vec2 newId, newId2;
    
    for(float x=-1.0; x<=1.0; x++){
        for(float y=-1.0; y<=1.0; y++){   
     		vec2 off = vec2(x,y);
            vec2 offId = id+off;
            vec2 posOff = offId;
            
            posOff += random(posOff, vec2(1.0), vec2(0.0));
            posOff.y += 0.1*sin(frac.x * PI);
            posOff.x += 0.1*sin(frac.y * PI);
            

            d = length(posOff - newUv);

            
            if(d < minDist)
            {
                minDist2 = minDist;
                newId2 = newId;
                
                minDist = d;
            	newId = offId;
            }else if(d < minDist2)
            {
                minDist2 = d;
                newId2 = offId;
            }
       	}
    }
    
    float val = smoothstep(0.05, 0.08, minDist2-minDist);
    col = mix(waterCol/2.25, waterCol/2., val);
    
    minDist = 100.0;
    minDist2 = 100.0;
    //uv+=time*0.1;
    newUv = scale*uv;
    newUv += vec2(5.0, 0.0);
	newUv /= z;
    
    frac = mod(newUv+vec2(0.5, 0.5), 1.0);
   	id = floor(newUv);
    
    newId, newId2;
    
    for(float x=-1.0; x<=1.0; x++){
        for(float y=-1.0; y<=1.0; y++){   
     		vec2 off = vec2(x,y);
            vec2 offId = id+off;
            vec2 posOff = offId;
            
            posOff += random(posOff, vec2(1.0), vec2(0.0));
            posOff.y += 0.1*sin(frac.x * PI);
            posOff.x += 0.1*sin(frac.y * PI);
            

            d = length(posOff - newUv);

            
            if(d < minDist)
            {
                minDist2 = minDist;
                newId2 = newId;
                
                minDist = d;
            	newId = offId;
            }else if(d < minDist2)
            {
                minDist2 = d;
                newId2 = offId;
            }
       	}
    }
    
    val = smoothstep(0.05, 0.06, minDist2-minDist);
    col += mix(vec3(1), waterCol/2., val);
    

    gl_FragColor = vec4(col,1);
}