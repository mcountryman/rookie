import TextField from "@material-ui/core/TextField";
import Grid from "@material-ui/core/Grid";
import * as React from "react";
import { useEffect, useState } from "react";

interface IProps {
  addSaveHandler: (handler: () => void) => void;
}

export const CameraDeviceId = (props: IProps) => {
  const [deviceId, setDeviceId] = useState(0);

  useEffect(() => {
    loadDeviceId()
      .then(deviceId => setDeviceId(deviceId))
      .catch(ex => console.error(ex))
    ;

    return () => {};
  }, []);

  props.addSaveHandler(() =>
    saveDeviceId(deviceId)
      .then(_ => console.log())
      .catch(ex => console.error(ex))
  );

  return (
    <Grid item xs={12}>
      <TextField
        id="device-id"
        type="number"
        label="Device Id"
        value={deviceId}
        onChange={(evt) => setDeviceId(Number(evt.target.value))}/>
    </Grid>
  );
}

async function saveDeviceId(value: number): Promise<void> {
  const res = await fetch(`/camera/id/${value}`, {method: "PATCH"});
  if (res.status != 200) {
    throw new Error(await res.json());
  }
}

async function loadDeviceId(): Promise<number> {
  const res = await fetch("/camera/id");
  if (res.status != 200) {
    throw new Error(await res.json());
  }

  return Number(await res.json());
}