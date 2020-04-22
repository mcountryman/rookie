import Grid from "@material-ui/core/Grid";
import TextField from "@material-ui/core/TextField";
import * as React from "react";

interface IProps {
  name: string,
  value: number,
  onChange: (value: number) => void,
}

export const CameraProperty = (props: IProps) => {
  return (
    <Grid item xs={12}>
      <TextField
        id={props.name}
        type="number"
        key={props.name}
        label={props.name}
        value={props.value}
        onChange={(evt) => props.onChange(Number(evt.target.value))}/>
    </Grid>
  );
}
