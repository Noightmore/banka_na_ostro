server {
    listen 80;
    server_name bank.com;
    root /var/www/bank.com;

    location / {
        try_files $uri $uri/ /index.fcgi?$query_string;
    }

    location ~ \.fcgi$ {
        include fastcgi_params;
        fastcgi_pass unix:/var/run/fcgiwrap.socket;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
        fastcgi_param PATH_INFO $fastcgi_path_info;
    }
}
