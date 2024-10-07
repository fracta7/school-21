FROM nginx:latest

RUN echo 'server {\n\
    listen 9090;\n\
    server_name localhost;\n\
    location / {\n\
        root   /usr/share/nginx/html;\n\
        index  index.html index.htm;\n\
    }\n\
}' > /etc/nginx/conf.d/default.conf

EXPOSE 9090

CMD ["nginx", "-g", "daemon off;"]