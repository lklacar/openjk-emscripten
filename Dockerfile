FROM nginx:1.30.7-alpine

COPY nginx.conf /etc/nginx/conf.d/default.conf
COPY bin/ /usr/share/nginx/html/

EXPOSE 8000

