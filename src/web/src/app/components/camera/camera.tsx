import * as React from "react";
import { useEffect, useState } from "react";


export const Camera = () => {
  const [dataUri, setDataUri] = useState("");

  useEffect(() => {
    const ws = new WebSocket("ws://localhost:8080/camera/ws");

    ws.onmessage = function handle({data}) {
      if (data instanceof Blob) {
        const reader = new FileReader();

        reader.onload = function load() {
          setDataUri(reader.result as string);
        };

        reader.readAsDataURL(data);
      }
    };

    return () => ws.close();
  }, []);

  return <img
    alt="camera"
    src={dataUri}
    width="100%"
  />;
};
