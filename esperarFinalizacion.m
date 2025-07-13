function esperarFinalizacion()
    urlStatus = 'http://192.168.4.1/status';
    opts = weboptions('Timeout', 10);
    
    fprintf('Esperando a que el ESP32 finalice el movimiento...\n');
    while true
        try
            estado = webread(urlStatus, opts);
            if strcmpi(estado, 'READY')
                fprintf('Movimiento finalizado.\n');
                break;
            end
        catch
            warning('No se pudo consultar el estado. Reintentando...');
        end
        pause(1); % Espera un segundo antes de volver a consultar
    end
end
