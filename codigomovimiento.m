% 1) tabla de puntos  [X  Y  thetaFinal]  (la 1.ª fila incluye θ0)
pts = [ ...
   
    0,0,0;% ← orientación inicial 

    0,0,0;
    ];

wrap = @(a) mod(a+180,360)-180;            % rango (-180,180]
fix180 = @(a) (a == -180).*180 + (a ~= -180).*a;

n  = size(pts,1);
orient = pts(1,3);                          

for i = 1:n-1    
    
    dx = pts(i+1,1) - pts(i,1);
    dy = pts(i+1,2) - pts(i,2);
    d  = hypot(dx,dy);
   ang = atan2d(dy,dx);
   
    if d < 1e-3                              % sólo giro
        giro1 = fix180(wrap(pts(i+1,3) - orient));
        dist  = 0;
        giro2 = 0;
    else                                     % giro-avance-giro
        ang     = atan2d(dy,dx);
        giro1   = wrap(ang - orient);
        sgn     = sign(giro1);               % guarda signo **antes**
        if abs(giro1) > 90                   % decide marcha atrás
            giro1 = wrap(giro1 - sgn*180);
            dist  = -d;
            ang   = wrap(ang  - sgn*180);
        else
            dist  =  d;
        end
        giro2 = fix180(wrap(pts(i+1,3) - ang));
    end

    % Limita el caso ±180 para el ESP32
    cmd = round([giro1, dist, giro2],1);
    cmd(cmd == -180) = 180;
    cmd(2)=cmd(2)*1.095/(0.796 * 1.064);
      cmd(1)=cmd(1)*3.72/(3.02 * 1.0142);
        cmd(3)=cmd(3)*3.72/(3.02 * 1.0142);
    enviarDatosESP32(cmd(1), cmd(2), cmd(3));
    esperarFinalizacion();
    pause(2);
    orient = pts(i+1,3);                     % siguiente referencia
end
