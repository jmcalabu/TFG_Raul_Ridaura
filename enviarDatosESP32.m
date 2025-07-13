function respuesta = enviarDatosESP32(v1, v2, v3)
% Enviar v1, v2, v3 al ESP32 y esperar confirmación "OK".

%  - Acepta enteros, decimales y notación científica (ej. 7.5e+2).
%  - Devuelve la respuesta cruda del ESP32 (normalmente "OK").
%  - Lanza un warning si no recibe "OK" en 30 s.

    
    % 1) Parámetros de red
    
    esp32_ip = '192.168.4.1'; %IP local
    opts     = weboptions('Timeout', 30, 'ContentType', 'text');

    
    % 2) Construir URL codificando +, espacios, etc.
    
    v1s = urlencode(sprintf('%.15g', v1));
    v2s = urlencode(sprintf('%.15g', v2));
    v3s = urlencode(sprintf('%.15g', v3));

    url = sprintf('http://%s/data?v1=%s&v2=%s&v3=%s', ...
                  esp32_ip, v1s, v2s, v3s);

    fprintf('Enviando datos: v1=%g, v2=%g, v3=%g\n', v1, v2, v3);

    
    % 3) Enviar GET y esperar la respuesta
   
    try
        respuesta = strtrim(webread(url, opts));   % ← dispara movimiento
        fprintf('Respuesta del ESP32: %s\n', respuesta);

        if ~strcmpi(respuesta, 'OK')
            warning('ESP32 devolvió "%s" (se esperaba "OK").', respuesta);
        end
    catch e
        warning('Error de comunicación con el ESP32: ' );
        respuesta = '';
    end
end
